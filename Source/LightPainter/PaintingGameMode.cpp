// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGameMode.h"

#include "PainterSaveGame.h"

#include "Kismet/StereoLayerFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void APaintingGameMode::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	SlotName = UGameplayStatics::ParseOption(Options, "SlotName");

	UE_LOG(LogTemp, Warning, TEXT("SlotName: %s"), *SlotName);
}

void APaintingGameMode::Save()
{
    UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (Painting)
	{
		Painting->SerializeFromWorld(GetWorld());
        Painting->Save();
	}else{
		UE_LOG(LogTemp, Warning, TEXT("Could not Save"));
	}
}

void APaintingGameMode::Load()
{
    UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (Painting)
	{
		Painting->DeserializeToWorld(GetWorld());

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game slot not found: %s"), *SlotName);
	}
}

void APaintingGameMode::SetStartLocation(FVector NewStartLocation)
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (Painting)
	{
		Painting->SetStartLocation(NewStartLocation);
		UE_LOG(LogTemp, Warning, TEXT("New Start Location: %f,%f,%f"), Painting->GetStartLocation().X,Painting->GetStartLocation().Y,Painting->GetStartLocation().Z);
		Painting->Save();

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game slot not found: %s"), *SlotName);
	}
}

FVector APaintingGameMode::GetStartLocation()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (Painting)
	{
		UE_LOG(LogTemp, Warning, TEXT("Get Start Location: %f,%f,%f"), Painting->GetStartLocation().X,Painting->GetStartLocation().Y,Painting->GetStartLocation().Z);
		return Painting->GetStartLocation();

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game slot not found: %s"), *SlotName);
		return FVector(-4860,2664,1121);
	}
}

void APaintingGameMode::SetHoops(int32 NewHoops)
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (Painting)
	{
		Painting->SetHoops(NewHoops);
		UE_LOG(LogTemp, Warning, TEXT("Current hoops after SetHoops: %d"), Painting->GetHoops());
		Painting->Save();

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game slot not found: %s"), *SlotName);
	}
}

int32 APaintingGameMode::GetHoops()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (Painting)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetHoops: %d"), Painting->GetHoops());
		return Painting->GetHoops();

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game slot not found: %s"), *SlotName);
		return -1;
	}
}

bool APaintingGameMode::IsRequiredHoops()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (Painting)
	{
		return Painting->GetHoops() >= RequiredHoops;

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game slot not found: %s"), *SlotName);
		return false;
	}
}

void APaintingGameMode::SaveAndQuit()
{
	SetStartLocation(UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation());
	
	Save();

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}



void APaintingGameMode::BeginPlay()
{
	Super::BeginPlay();

	Load();
    UStereoLayerFunctionLibrary::HideSplashScreen();
} 