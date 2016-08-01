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
	USkeletalMeshComponent* GetMesh() const { return WeaponMesh; }

public:
	/** attach the visuals to Owner's first person view */
	UFUNCTION(BlueprintNativeEvent)
	void AttachToOwner();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* WeaponMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	/** socket to attach weapon to hands; if None, then the hands are hidden */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName HandsAttachSocketName;
};
