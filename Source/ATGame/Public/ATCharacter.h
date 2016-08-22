// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ATCharacter.generated.h"

UCLASS()
class ATGAME_API AATCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:
	virtual void PossessedBy(AController* NewController) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);

	virtual void SpecialSkill();
	virtual void Attack(EAttackType EType, int AnimationState = 0);

	void GetCameraLookatVector(FVector& Lookat, FRotator& CameraRotate);

	// ���� x,y �̵� Vector�� Camera�������� �� ��ȯ
	void GetRotateVectorByCamera(FVector& RotateVector);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual bool AddInventory(AATInventory* InvToAdd, bool bAutoActivate);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void RemoveInventory(AATInventory* InvToRemove);

	virtual void AddDefaultInventory(TArray<TSubclassOf<AATInventory>> DefaultInventoryToAdd);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
	class USkeletalMeshComponent* CapeSkeletalMeshComponent;

	/** Camera�� �ѷ� �δ� Component - ���� �ε��� Camera ó�� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraCapsuleComponent;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CharacterCameraComponent;

	UPROPERTY()
	FVector CameraLookat;

	UPROPERTY()
	FRotator CameraRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage")
	TArray<UAnimMontage*> AttackMontageList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage")
	TArray<UAnimMontage*> AttackEndMontageList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<TSubclassOf<class AATInventory>> CharacterInventory;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	AATInventory* InventoryList;

	EAttackType AttackType;
};
