// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATUserWidget.h"

UATUserWidget::UATUserWidget(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UATUserWidget::AttachToController(AATPlayerController* Controller)
{
	if (GetWorld()->GetNetMode() == NM_DedicatedServer)
		return;

	if (Controller && Controller->IsLocalController())
	{
		OwnerController = Controller;
		AddToViewport(UIDepth);
	}
}


void UATUserWidget::DetachFromController()
{
	if (GetWorld()->GetNetMode() == NM_DedicatedServer)
		return;

	if (OwnerController)
	{
		OwnerController = nullptr;
	}
}


