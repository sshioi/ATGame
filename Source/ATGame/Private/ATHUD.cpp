// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATHUD.h"

AATHUD::AATHUD(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> HealthHPObj(TEXT("/Game/UI/InGame/HPBar"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> BarFillObj(TEXT("/Game/UI/InGame/HPBG"));
	
	HealthTexture = HealthHPObj.Object;
	BarFillTexture = BarFillObj.Object;
	
	HealthBarHeightRatio = 18.f;
	HealthBarWidthRatio = 0.7f;
}

void AATHUD::DrawHUD()
{
	if (GEngine && GEngine->GameViewport)
	{
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		UIScale = ViewportSize.X / 2048.0f;
	}

	Super::DrawHUD();

	DrawActorsHealth();
}

void AATHUD::DrawActorsHealth()
{
	for (FConstPawnIterator Iterator = GetWorld()->GetPawnIterator(); Iterator; ++Iterator)
	{
		AATCharacter* Character = Cast<AATCharacter>(*Iterator);
		if (Character != NULL && Character->Health > 0)
		{
			DrawHealthBar(Character, Character->Health / (float)Character->HealthMax, HealthBarHeightRatio * UIScale, Character->HealthOffsetY);
		}
	}
}

void AATHUD::DrawHealthBar(AATCharacter* Character, float HealthPercentage, int32 BarHeight, int32 OffsetY) const
{
	FVector2D Center2D = FVector2D(Canvas->Project(Character->GetActorLocation()));

	if (Center2D.IsZero())
	{
		return;
	}

	FVector Pos1 = Canvas->Project(FVector(Character->GetActorLocation().X, Character->GetActorLocation().Y - Character->HealthActorExtent * 2, Character->GetActorLocation().Z));
	FVector Pos2 = Canvas->Project(FVector(Character->GetActorLocation().X, Character->GetActorLocation().Y + Character->HealthActorExtent * 2, Character->GetActorLocation().Z));
	float HealthBarLength = ((Pos2 - Pos1).Size2D()) * (HealthBarWidthRatio * UIScale);

	float X = Center2D.X - HealthBarLength * 0.5f;
	float Y = Center2D.Y - OffsetY;
	FCanvasTileItem TileItem(FVector2D(X, Y), HealthTexture->Resource, FVector2D(HealthBarLength * HealthPercentage, BarHeight), FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	TileItem.UV1 = FVector2D(HealthPercentage, 1.0f);
	Canvas->DrawItem(TileItem);

	//Fill the rest of health with gray gradient texture
	X = Center2D.X - (HealthBarLength * 0.5f) + HealthBarLength * HealthPercentage;
	Y = Center2D.Y - OffsetY;
	TileItem.Position = FVector2D(X, Y);
	TileItem.Texture = BarFillTexture->Resource;
	TileItem.UV1 = FVector2D(1.0f, 1.0f);
	TileItem.Size = FVector2D(HealthBarLength * (1.0f - HealthPercentage), BarHeight);
	TileItem.SetColor(FLinearColor(0.5f, 0.5f, 0.5f, 0.5f));
	Canvas->DrawItem(TileItem);
}