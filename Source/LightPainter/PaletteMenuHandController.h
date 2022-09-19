// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandControllerBase.h"

#include "Components/WidgetComponent.h"

#include "PaletteMenuHandController.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API APaletteMenuHandController : public AHandControllerBase
{
	GENERATED_BODY()

public:
	APaletteMenuHandController();

	void ToggleMenuPressed() override;

private:

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* PaletteMenu;

	UPROPERTY(EditAnywhere)
	class USoundBase* ToggleSoundOn;

	UPROPERTY(EditAnywhere)
	class USoundBase* ToggleSoundOff;
	
	bool isActive = true;
};
