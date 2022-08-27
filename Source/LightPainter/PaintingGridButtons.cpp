// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGridButtons.h"

bool UPaintingGridButtons::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!AddButton) return false;
	AddButton->OnClicked.AddDynamic(this, &UPaintingGridButtons::AddButtonClicked);

	if (!DeleteButton) return false;
	DeleteButton->OnClicked.AddDynamic(this, &UPaintingGridButtons::DeleteButtonClicked);

	return true;
}