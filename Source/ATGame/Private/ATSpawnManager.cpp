// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATSpawnManager.h"


// Sets default values
AATSpawnManager::AATSpawnManager(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

// Called when the game starts or when spawned
void AATSpawnManager::BeginPlay()
{
	Super::BeginPlay();

	InitSpawn(SpawnTable);
}

void AATSpawnManager::InitSpawn(TAssetPtr<UDataTable>& Table)
{
	UDataTable* SpawnTableAsset = (Table.IsNull()) ? nullptr : Table.LoadSynchronous();

	if (SpawnTableAsset == nullptr)
	{
		return;
	}

	// 월드에 있는 AATSpawner가지고 와서 SpawnerList넣어준다.
	TArray<AActor*> ActorsArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AATSpawner::StaticClass(), ActorsArray);

	for (auto Spawne = ActorsArray.CreateIterator(); Spawne; ++Spawne)
	{
		AATSpawner* ATSpawne = Cast<AATSpawner>(*Spawne);
		if (ATSpawne != nullptr)
		{
			for (auto TableKey : SpawnTableAsset->GetRowNames())
			{
				FATSpawnInfo* SpawnInfo = SpawnTable->FindRow<FATSpawnInfo>(TableKey, TEXT("ATSpawnInfo"));
				if (SpawnInfo->SpawnType == ATSpawne->SpawnType)
				{
					if (SpawnInfo->SpawnActorAsset.IsNull() == false)
					{
						const FStringAssetReference& AssetReference = SpawnInfo->SpawnActorAsset.ToStringReference();
						AATCharacterAI* CharacterAI = Cast<AATCharacterAI>(ATSpawne->Spawn(Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *AssetReference.ToString(), nullptr, LOAD_NoWarn))));

						if (CharacterAI->Controller == nullptr)
						{
							CharacterAI->SpawnDefaultController();
						}
					}
					break;
				}
			}
		}
	}
}
