// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "PaintingGrid.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTIONç(BlueprintCallable)
	void AddPainting();

protected:

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,meta = (BindWidget))
	UUniformGridPanel* PaintingGrid;

	
};
