// Fill out your copyright notice in the Description page of Project Settings.


#include "UIPointerHandController.h"
#include "Components/WidgetInteractionComponent.h"

AUIPointerHandController::AUIPointerHandController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	Interaction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Interaction"));
	Interaction->SetupAttachment(GetRootComponent());

}

void AUIPointerHandController::TriggerPressed()
{
	Interaction->PressPointerKey(EKeys::LeftMouseButton);
}

void AUIPointerHandController::TriggerReleased()
{
	Interaction->ReleasePointerKey(EKeys::LeftMouseButton);
}