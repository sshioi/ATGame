// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATPlayerController.h"

AATPlayerController::AATPlayerController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	PlayerCameraManagerClass = APlayerCameraManager::StaticClass();
}

void AATPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();

	for (int Index = 0; Index < DisplayWidgetList.Num(); ++Index)
	{
		CurrentWidget = CreateWidget<UUserWidget>(this, DisplayWidgetList[Index]);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport(Index);
		}
	}
}

void AATPlayerController::SetPawn(APawn* InPawn)
{
	if (InPawn == nullptr)
	{
		// Attempt to move the PC to the current camera location if no pawn was specified
		const FVector NewLocation = (PlayerCameraManager != nullptr) ? PlayerCameraManager->GetCameraLocation() : GetSpawnLocation();
		SetSpawnLocation(NewLocation);
	}

	AController::SetPawn(InPawn);

	ATCharacter = Cast<AATCharacter>(InPawn);
}

void AATPlayerController::InitInputSystem()
{
	Super::InitInputSystem();
}

void AATPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AATPlayerController::MoveForward);
	InputComponent->BindAxis("MoveBackward", this, &AATPlayerController::MoveBackward);
	InputComponent->BindAxis("MoveLeft", this, &AATPlayerController::MoveLeft);
	InputComponent->BindAxis("MoveRight", this, &AATPlayerController::MoveRight);
}

void AATPlayerController::MoveForward(float Value)
{
	if (Value != 0.0f && ATCharacter != nullptr)
	{
		ATCharacter->MoveForward(Value);
		StickMoveDirection.X = Value;
		UpdateInputRotate();
	}
}

void AATPlayerController::MoveBackward(float Value)
{
	MoveForward(Value * -1);
}

void AATPlayerController::MoveLeft(float Value)
{
	MoveRight(Value * -1);
}

void AATPlayerController::MoveRight(float Value)
{
	if (Value != 0.0f && ATCharacter != nullptr)
	{
		ATCharacter->MoveRight(Value);
		StickMoveDirection.Y = Value;
		UpdateInputRotate();
	}
}

void AATPlayerController::UpdateInputRotate()
{
	if (GetWorld()->GetNetMode() != NM_DedicatedServer)
	{
		FRotator PredictionRotator(GetControlRotation());
		UpdatePredictionRotator(PredictionRotator);
		SetControlRotation(PredictionRotator);
	}
}

void AATPlayerController::UpdatePredictionRotator(FRotator& PredictionRotator)
{
	// Input Direction은 2차원 xy 절대좌표이므로 Camera Default yaw에 맞춰 회전시킴
	StickMoveDirection.Normalize();
	FVector StickToWorld = StickMoveDirection;
	ATCharacter->GetRotateVectorByCamera(StickToWorld);

	PredictionRotator = StickToWorld.Rotation();
}

void AATPlayerController::ClientSetHUD_Implementation(TSubclassOf<class AHUD> NewHUDClass)
{
	Super::ClientSetHUD_Implementation(NewHUDClass);

	if (MyHUD != nullptr)
	{
		MyATHUD = Cast<AATHUD>(MyHUD);
	}
}