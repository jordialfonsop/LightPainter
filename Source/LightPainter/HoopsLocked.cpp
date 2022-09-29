// Fill out your copyright notice in the Description page of Project Settings.


#include "HoopsLocked.h"
#include "PaintingGameMode.h"
#include "Internationalization/Text.h"

void UHoopsLocked::SetRequiredCount()
{
    APaintingGameMode* GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());
    
    FString HoopsNum = FString::FromInt(GameMode->GetRequiredHoops());

    Count->SetText(FText::FromString(HoopsNum));

    UE_LOG(LogTemp, Warning, TEXT("Hoops Required: %d"), GameMode->GetRequiredHoops());
}