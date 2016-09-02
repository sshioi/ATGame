// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ATInventory.h"
#include "ATWeapon.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, Abstract, NotPlaceable)
class ATGAME_API AATWeapon : public AATInventory
{
	GENERATED_UCLASS_BODY()

public:
	virtual void GivenTo(AATCharacter* NewOwner, bool bAutoActivate) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void AttachToOwner();

	UFUNCTION()
	virtual void DetachFromOwner();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void FireShot();

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	virtual AATProjectile* FireProjectile(const TSubclassOf<AATProjectile>& ProjectileClass);

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AATProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float Damage;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* WeaponMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = " Component")
	class UCapsuleComponent* MeleeCollision;

	/** socket to attach weapon to hands; if None, then the hands are hidden */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName HandsAttachSocketName;

#if WITH_EDITOR
	UPROPERTY()
	bool bIsDrawWeaponCollision;
#endif	// WITH_EDITOR
};
