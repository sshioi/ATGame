// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ATPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ATGAME_API AATPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

public:
	virtual void ReceivedPlayer() override;
	virtual void SetPawn(APawn* InPawn) override;

	// Input
	virtual void SetupInputComponent() override;
	virtual void InitInputSystem() override;

	virtual void MoveForward(float Value);
	virtual void MoveBackward(float Value);
	virtual void MoveLeft(float Value);
	virtual void MoveRight(float Value);

	virtual void UpdateInputRotate();
	virtual void UpdatePredictionRotator(FRotator& PredictionRotator);

	UFUNCTION(BlueprintCallable, Category = "HUD", Reliable, Client)
	void ClientSetHUD(TSubclassOf<class AHUD> NewHUDClass);

private:
	UPROPERTY()
	AATCharacter* ATCharacter;

	UPROPERTY()
	class AATHUD* MyATHUD;

	UPROPERTY()
	TSubclassOf<class AHUD> HUDClass;

public:
	UPROPERTY()
	FVector StickMoveDirection;

	// �迭�ڸ��� Depth���̴�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMG Widget")
	TArray<TSubclassOf<class UUserWidget>> DisplayWidgetList;

	UPROPERTY()
	UUserWidget* CurrentWidget;
};
