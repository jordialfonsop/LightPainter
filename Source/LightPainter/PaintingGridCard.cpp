// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGridCard.h"


void UPaintingGridCard::SetPaintingName(FString Name)
{
	SlotName->SetText(FText::FromString(Name));

	CardButton->OnClicked.AddDynamic(this,&UPaintingGridCard::CardButtonClicked);
}

void UPaintingGridCard::CardButtonClicked()
{

	if(PaintingPicker->GetDeleteMode()){
		PaintingPicker->DeleteItem(PaintingName);
	}else{
		UStereoLayerFunctionLibrary::ShowSplashScreen();

		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Canvas"), true, "SlotName=" + PaintingName);
		UE_LOG(LogTemp,Warning,TEXT("options is in cardbuttonClicked : %s"),*PaintingName);

	}

}