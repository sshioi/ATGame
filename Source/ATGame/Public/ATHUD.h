// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "ATHUD.generated.h"

/**
 * 
 */
UCLASS()
class ATGAME_API AATHUD : public AHUD
{
	GENERATED_UCLASS_BODY()
public:
	// Begin HUD interface
	virtual void DrawHUD() override;

	//Draw health bars for actors
	void DrawActorsHealth();

	/**
	* Draws health bar for specific actor.
	*
	* @param	AICharacter	Actor for which the health bar is for.
	* @param	HealthPct	Current Health percentage.
	* @param	BarHeight	Height of the health bar
	* @param	OffsetY		Y Offset of the health bar.
	*/
	void DrawHealthBar(AATCharacter* AICharacter, float HealthPct, int32 BarHeight, int OffsetY = 0) const;

protected:
	UPROPERTY()
	class UTexture2D* HealthTexture;
	
	UPROPERTY()
	class UTexture2D* BarFillTexture;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	float HealthBarHeightRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	float HealthBarWidthRatio;

	/** current UI scale */
	float UIScale;
};
