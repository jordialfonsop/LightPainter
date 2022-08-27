// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "PaintingPicker.h"

#include "PaintingGridButtons.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingGridButtons : public UUserWidget
{
	GENERATED_BODY()

public:
	int test;
	bool Initialize() override;

	void SetParentPicker(APaintingPicker* NewPainterPicker) {ParentPicker = NewPainterPicker;}

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* AddButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* DeleteButton;

private:
	UFUNCTION()
	void AddButtonClicked() 
	{
		if(ParentPicker){
			ParentPicker->AddPainting();
		}
	}

	UFUNCTION()
	void DeleteButtonClicked()
	{
		if(ParentPicker){
			ParentPicker->ToggleDeleteMode();
		}
	}

	UPROPERTY()
	APaintingPicker* ParentPicker;
};
