// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ATUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ATGAME_API UATUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UATUserWidget(const FObjectInitializer& ObjectInitializer);

	virtual void AttachToController(AATPlayerController* Controller);
	virtual void DetachFromController();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WidgetInfo")
	FString WidgetName;

	UPROPERTY(EditAnywhere, Category = "DepthOrder")
	int16 UIDepth;

	UPROPERTY(BlueprintReadOnly, Category = "Controller")
	AATPlayerController* OwnerController;
};
