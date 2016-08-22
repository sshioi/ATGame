// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATPlayerState.h"
#include "ATGameGameMode.h"

AATPlayerState::AATPlayerState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

AATCharacter* AATPlayerState::GetATCharacter()
{
	AController* Controller = Cast<AController>(GetOwner());
	if (Controller != nullptr)
	{
		AATCharacter* Character = Cast<AATCharacter>(Controller->GetPawn());
		if (Character != nullptr)
		{
			return Character;
		}
	}
	return nullptr;
}

void AATPlayerState::ApplyItem()
{
	// 로비에서 InGame 아이템이 추가시 ItemBase 생성
	// ItemBase를 따라서 Item 적용 [ Weapon / Equipment / Accessory 등등 ]
	// 일단 강제로 DefaultInventory Item 적용

	AATCharacter* OwnerCharacter = GetATCharacter();
	AATGameGameMode* ATGameMode = GetWorld()->GetAuthGameMode<AATGameGameMode>();

	if (OwnerCharacter && OwnerCharacter->CharacterInventory.Num() != 0 && ATGameMode)
	{
		OwnerCharacter->AddDefaultInventory(ATGameMode->GameModeInventory);
	}
}
