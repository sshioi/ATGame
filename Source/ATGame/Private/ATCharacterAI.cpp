// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATCharacterAI.h"

AATCharacterAI::AATCharacterAI(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.DoNotCreateDefaultSubobject(TEXT("CharacterCameraComp")).DoNotCreateDefaultSubobject(TEXT("CameraCapsuleComp")))
{
	AttackCollisionSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("AttackCollisionSphere"));
	if (AttackCollisionSphere != nullptr)
	{
		AttackCollisionSphere->SetupAttachment(GetMesh());
	}
	Damage = 10.f;
	DistanceSquared = 30000.f;
	AttackDistance = 150.f;
	AreaRadius = 200.f;

	AIControllerClass = AATAIController::StaticClass();
}

void AATCharacterAI::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AATPlayerState* ATPS = Cast<AATPlayerState>(PlayerState);
	if (ATPS != nullptr)
	{
		ATPS->bIsABot = true;
	}
}

void AATCharacterAI::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(AATCharacter::StaticClass()) && PlayerState != nullptr && !PlayerState->bIsABot)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, NULL, this, UDamageType::StaticClass());
	}
}

void AATCharacterAI::FaceRotation(FRotator NewControlRotation, float DeltaTime)
{
	FRotator CurrentRotator = FMath::RInterpTo(GetActorRotation(), NewControlRotation, DeltaTime, 8.f);

	Super::FaceRotation(NewControlRotation, DeltaTime);
}
