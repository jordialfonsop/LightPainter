// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SaveGame.h"
#include "EngineUtils.h"
#include "Misc/Guid.h"
#include "PainterSaveGameIndex.h"
#include "HAL/FileManager.h"

#include "Stroke.h"

UPainterSaveGame * UPainterSaveGame::Create()
{
	UPainterSaveGame* NewSaveGame = Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	NewSaveGame->SlotName = FGuid::NewGuid().ToString();
	NewSaveGame->Hoops = 0;
	NewSaveGame->StartLocation = FVector(-4860,2664,1121);
	if(!NewSaveGame->Save()) return nullptr;

	UPainterSaveGameIndex* Index = UPainterSaveGameIndex::Load();
	Index->AddSaveGame(NewSaveGame);
	Index->Save();
	return NewSaveGame;
}

UPainterSaveGame* UPainterSaveGame::Load(FString SlotName)
{
    return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

void UPainterSaveGame::Delete()
{
	
	auto List = UPainterSaveGameIndex::Load();
	List->RemovePainting(SlotName);
	List->Save();

	UGameplayStatics::DeleteGameInSlot(SlotName, 0);
	
}

void UPainterSaveGame::SerializeFromWorld(UWorld * World)
{
	Strokes.Empty();
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		//TODO:Serialize
		Strokes.Add(StrokeItr->SerializeToStruct());
	}
}

void UPainterSaveGame::DeserializeToWorld(UWorld * World)
{
	ClearWorld(World);
	for (FStrokeState StrokeState : Strokes)
	{
		AStroke::SpawnAndDeserializeFromStruct(World, StrokeState);
	}
}

void UPainterSaveGame::ClearWorld(UWorld * World)
{
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		StrokeItr->Destroy();
	}
}
