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
	// �κ񿡼� InGame �������� �߰��� ItemBase ����
	// ItemBase�� ���� Item ���� [ Weapon / Equipment / Accessory ��� ]
	// �ϴ� ������ DefaultInventory Item ����

	AATCharacter* OwnerCharacter = GetATCharacter();
	AATGameGameMode* ATGameMode = GetWorld()->GetAuthGameMode<AATGameGameMode>();

	if (OwnerCharacter && OwnerCharacter->CharacterInventory.Num() != 0 && ATGameMode)
	{
		OwnerCharacter->AddDefaultInventory(ATGameMode->GameModeInventory);
	}
}
