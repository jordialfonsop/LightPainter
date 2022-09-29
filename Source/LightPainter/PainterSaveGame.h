// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PainterSaveGame.generated.h"

USTRUCT()
struct FStrokeState
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<class AStroke> Class;

	UPROPERTY()
	TArray<FVector> ControlPoints;

};

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPainterSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	static UPainterSaveGame* Create();
	static UPainterSaveGame* Load(FString SlotName);

	bool Save();
	void Delete();

	void SetState(FString NewState) { State = NewState; }
	FString GetState() const { return State; }

	UFUNCTION(BlueprintCallable)
	void SetHoops(int32 NewHoops) { Hoops = NewHoops; }
	UFUNCTION(BlueprintCallable)
	int32 GetHoops() { return Hoops; }

	UFUNCTION(BlueprintCallable)
	void SetStartLocation(FVector NewStartLocation) { StartLocation.Set(NewStartLocation.X,NewStartLocation.Y,NewStartLocation.Z); }
	UFUNCTION(BlueprintCallable)
	FVector GetStartLocation() { return StartLocation; }

	void SerializeFromWorld(UWorld * World);
	void DeserializeToWorld(UWorld * World);

	FString GetSlotName() const { return SlotName; }

private:

	void ClearWorld(UWorld * World);

	UPROPERTY()
	FString State;

	UPROPERTY()
	FString SlotName;

	UPROPERTY()
	TArray<FStrokeState> Strokes;

	UPROPERTY(EditAnywhere)
	int32 Hoops;

	UPROPERTY(EditAnywhere)
	FVector StartLocation;
	
};
