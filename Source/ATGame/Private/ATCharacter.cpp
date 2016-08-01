// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATCharacter.h"


// Sets default values
AATCharacter::AATCharacter(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	if (GetMesh())
	{
		GetMesh()->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->bEnablePhysicsOnDedicatedServer = true; // needed for feign death; death ragdoll shouldn't be invoked on server

		CapeSkeletalMeshComponent = ObjectInitializer.CreateOptionalDefaultSubobject<USkeletalMeshComponent>(this, TEXT("CapeSkeletalMeshComp"));
		if (CapeSkeletalMeshComponent != nullptr)
		{
			CapeSkeletalMeshComponent->SetupAttachment(GetMesh(), TEXT("Cape"));
			CapeSkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			CapeSkeletalMeshComponent->SetCastShadow(false);
		}
	}

	CameraCapsuleComponent = ObjectInitializer.CreateOptionalDefaultSubobject<USpringArmComponent>(this, TEXT("CameraCapsuleComp"));
	if (CameraCapsuleComponent)
	{
		CameraCapsuleComponent->SetupAttachment(GetCapsuleComponent());
		CameraCapsuleComponent->bUsePawnControlRotation = false; // Rotate the arm based on the controller

																 // Create a follow camera
		CharacterCameraComponent = ObjectInitializer.CreateOptionalDefaultSubobject<UCameraComponent>(this, TEXT("CharacterCameraComp"));
		if (CharacterCameraComponent != nullptr)
		{
			// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
			CharacterCameraComponent->SetupAttachment(CameraCapsuleComponent, USpringArmComponent::SocketName);
			CharacterCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
		}
	}

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AATCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCameraLookatVector(CameraLookat, CameraRotation);
}

// Called every frame
void AATCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AATCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AATCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation(0.f, CameraLookat.Rotation().Yaw, 0.f);
		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void AATCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation(0.f, CameraLookat.Rotation().Yaw, 0.f);
		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

void AATCharacter::GetCameraLookatVector(FVector& Lookat, FRotator& CameraRotate)
{
	if (CameraCapsuleComponent == nullptr)
	{
		Lookat = GetActorLocation();
		CameraRotate = GetActorRotation();
		return;
	}

	CameraRotate = FRotator(0.f, CameraCapsuleComponent->GetRelativeTransform().GetRotation().Rotator().Yaw, 0.f);
	Lookat = CameraRotate.RotateVector(FVector::ForwardVector);
}

void AATCharacter::GetRotateVectorByCamera(FVector& RotateVector)
{
	RotateVector = FRotationMatrix(CameraRotation).TransformVector(RotateVector);
}

bool AATCharacter::AddInventory(AATInventory* InvToAdd, bool bAutoActivate)
{
	if (InvToAdd != NULL && !InvToAdd->IsPendingKillPending())
	{
		if (InventoryList == NULL)
		{
			InventoryList = InvToAdd;
		}
		/*else
		{
		}*/
		return true;
	}
	return false;
}

void AATCharacter::RemoveInventory(AATInventory* InvToRemove)
{
	/*if (InvToRemove != NULL && InventoryList != NULL)
	{
		bool bFound = false;
		if (InvToRemove == InventoryList)
		{
			bFound = true;
			InventoryList = InventoryList->NextInventory;
		}
		else
		{
			for (AATInventory* TestInv = InventoryList; TestInv->NextInventory != NULL; TestInv = TestInv->NextInventory)
			{
				if (TestInv->NextInventory == InvToRemove)
				{
					bFound = true;
					TestInv->NextInventory = InvToRemove->NextInventory;
					break;
				}
			}
		}
		if (bFound)
		{
			InvToRemove->Removed();
		}
	}*/
}

void AATCharacter::AddDefaultInventory(TArray<TSubclassOf<AATInventory>> DefaultInventoryToAdd)
{
	// 캐릭터가 가지고 있는 인벤토리
	for (int32 i = 0; i<DefaultCharacterInventory.Num(); i++)
	{
		AddInventory(GetWorld()->SpawnActor<AATInventory>(DefaultCharacterInventory[i], FVector(0.0f), FRotator(0, 0, 0)), true);
	}

	// 모드 전용 인벤토리
	for (int32 i = 0; i<DefaultInventoryToAdd.Num(); i++)
	{
		AddInventory(GetWorld()->SpawnActor<AATInventory>(DefaultInventoryToAdd[i], FVector(0.0f), FRotator(0, 0, 0)), true);
	}
}