
// Fill out your copyright notice in the Description page of Project Settings.


#include "HoopCount.h"
#include "PaintingGameMode.h"
#include "Internationalization/Text.h"


void UHoopCount::SetCount()
{
    APaintingGameMode* GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());

    FString HoopsNum = FString::FromInt(GameMode->GetHoops());

    Count->SetText(FText::FromString(HoopsNum));

    UE_LOG(LogTemp, Warning, TEXT("Hoops Count: %d"), GameMode->GetHoops());
}
