// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ATWeapon.h"
#include "ATWeapon_Shield.generated.h"

/**
 * 
 */
UCLASS()
class ATGAME_API AATWeapon_Shield : public AATWeapon
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* ShieldMeshComponent;
	
};
