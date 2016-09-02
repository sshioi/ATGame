// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ATCharacter.generated.h"

USTRUCT()
struct FWeaponInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	class AATWeapon* ATWeapon;

	UPROPERTY()
	FName SocketName;
};

UCLASS()
class ATGAME_API AATCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:
	virtual void PossessedBy(AController* NewController) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);

	virtual void Attack(EAttackType EType, int AnimationState = 0);

	void GetCameraLookatVector(FVector& Lookat, FRotator& CameraRotate);

	// 절대 x,y 이동 Vector를 Camera시점으로 재 변환
	void GetRotateVectorByCamera(FVector& RotateVector);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual bool AddInventory(AATInventory* InvToAdd, bool bAutoActivate);

	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//virtual void RemoveInventory(AATInventory* InvToRemove);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StartFire(FName Socket);

	virtual void AddDefaultInventory(TArray<TSubclassOf<AATInventory>> DefaultInventoryToAdd);

	virtual void NotifyTakeHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	virtual void OnDied(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

	void OnDiedAnimationEnd();
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE UATAnimInstance* GetATAnimInstance()
	{
		return ATAnimInstance != nullptr ? ATAnimInstance : nullptr;
	}

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USkeletalMeshComponent* CapeSkeletalMeshComponent;

	/** Camera를 둘러 싸는 Component - 벽에 부딪힐 Camera 처리 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraCapsuleComponent;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CharacterCameraComponent;

	UPROPERTY()
	FVector CameraLookat;

	UPROPERTY()
	FRotator CameraRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage")
	TArray<class UAnimMontage*> AttackMontageList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage")
	class UAnimMontage* FlinchMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage")
	class UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage")
	class UAnimMontage* BlockMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<TSubclassOf<class AATInventory>> CharacterInventory;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	class AATInventory* InventoryList;

	UPROPERTY()
	TArray<FWeaponInfo> ATWeaponList;

	// AI만 Firing Delay 적용
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float FiringDelay;

	UPROPERTY()
	bool bIsAttacking;

	EAttackType AttackType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Health)
	float Health;

	UPROPERTY()
	class AATWeapon* CurrentWeapon;

protected:
	UPROPERTY()
	class UATAnimInstance* ATAnimInstance;

	float OrgMaxWalkSpeed;
};
