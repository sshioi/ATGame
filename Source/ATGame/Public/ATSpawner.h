// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ATSpawner.generated.h"

UENUM(BlueprintType)
enum class ESpawnType : uint8
{
	Melee,
	Magic,
	None,
};

USTRUCT(Blueprintable)
struct FATSpawnInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// �߰� ������ ������ ���� �߰�!
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ESpawnType SpawnType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TAssetSubclassOf<AATCharacter> SpawnActorAsset;
};

UCLASS(Blueprintable)
class ATGAME_API AATSpawner : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Spawn)
	virtual AATCharacter* Spawn(UClass* SpawnClass);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESpawnType SpawnType;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UArrowComponent* SpawnerArrow;
#endif
};
