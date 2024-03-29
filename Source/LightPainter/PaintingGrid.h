// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/HorizontalBox.h"
#include "PaginationDot.h"
#include "PaintingGrid.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void AddPainting(int32 PaintingIndex, FString PaintingName, APaintingPicker* PaintingPicker);
	void AddPaginationDot(bool Active);

	void ClearPaintings();
	void ClearPaginationDots();

	UFUNCTION(BlueprintCallable)
	void SetDeleteMode(bool NewDeleteMode){DeleteMode = NewDeleteMode;};

	UFUNCTION(BlueprintCallable)
	bool GetDeleteMode(){return DeleteMode;};

	int32 GetNumberOfSlots() const;

protected:

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,meta = (BindWidget))
	UUniformGridPanel* PaintingGrid;

	UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* PaginationDots;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPaintingGridCard> GridCardClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaginationDot> PaginationDotClass;

	UPROPERTY(EditDefaultsOnly)
	float PaginationDotPadding = 8;

	bool DeleteMode = false;
	
};
