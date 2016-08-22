// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ATWeapon.h"
#include "ATWeapon_Melee.generated.h"

/**
 * 
 */
UCLASS()
class ATGAME_API AATWeapon_Melee : public AATWeapon
{
	GENERATED_UCLASS_BODY()

public:
	/** particle component for muzzle flash */
	UPROPERTY(EditAnywhere, Category = "Component")
	UParticleSystemComponent* PSCSwing;

	/** socket to attach weapon to hands; if None, then the hands are hidden */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName SwingSocketName;
};
