// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATProjectile.h"


// Sets default values
AATProjectile::AATProjectile(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	if (ProjectileCollision != nullptr)
	{
		//RootComponent = ProjectileCollision;
		ProjectileCollision->SetupAttachment(RootComponent);
		ProjectileCollision->InitSphereRadius(11.f);
		ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &AATProjectile::OnOverlapBegin);
		ProjectileCollision->BodyInstance.SetCollisionProfileName("Projectile");
		ProjectileCollision->bTraceComplexOnMove = true;
		ProjectileCollision->bReceivesDecals = false;

		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		if (ProjectileMeshComponent != nullptr)
		{
			ProjectileMeshComponent->SetupAttachment(ProjectileCollision);
			ProjectileMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			ProjectileMeshComponent->SetCastShadow(false);
		}

		ImpactEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ImpactEffect"));
		if (ImpactEffect != nullptr)
		{
			ImpactEffect->SetupAttachment(ProjectileCollision);
			ImpactEffect->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	if (ProjectileMovement != nullptr)
	{
		ProjectileMovement->SetUpdatedComponent(ProjectileCollision);
		ProjectileMovement->bShouldBounce = false;
		ProjectileMovement->InitialSpeed = 1000.0f;
		ProjectileMovement->MaxSpeed = 1000.0f;
	}

	InitialLifeSpan = 3.0f;
}

void AATProjectile::OnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AATCharacter* Charater = Cast<AATCharacter>(OtherActor);
		if (Charater != nullptr && !Charater->PlayerState->bIsABot)
		{
			Destroy();
			UGameplayStatics::ApplyPointDamage(SweepResult.Actor.Get(), Damage, -SweepResult.ImpactNormal, SweepResult, NULL, this, UDamageType::StaticClass());
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("Projectile Collision"));
		}
	}
}