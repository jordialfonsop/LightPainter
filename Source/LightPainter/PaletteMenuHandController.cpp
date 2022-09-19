// Fill out your copyright notice in the Description page of Project Settings.


#include "PaletteMenuHandController.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

APaletteMenuHandController::APaletteMenuHandController()
{
	PaletteMenu = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaletteMenu"));
	PaletteMenu->SetupAttachment(GetRootComponent());
}

void APaletteMenuHandController::ToggleMenuPressed()
{
	isActive = !isActive;
	if (isActive){
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),ToggleSoundOn,GetActorLocation(),3.0f);
	}else{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),ToggleSoundOff,GetActorLocation(),3.0f);
	}
	PaletteMenu->SetActive(isActive);
	PaletteMenu->SetVisibility(isActive);
}