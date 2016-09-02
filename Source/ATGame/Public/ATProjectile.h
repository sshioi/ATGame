// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ATProjectile.generated.h"

UCLASS()
class ATGAME_API AATProjectile : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	FORCEINLINE class USphereComponent* GetProjectileCollision() const { return ProjectileCollision; }

	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

public:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	class UParticleSystemComponent* ImpactEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Component")
	class USphereComponent* ProjectileCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* ProjectileMeshComponent;

	float Damage;
};
