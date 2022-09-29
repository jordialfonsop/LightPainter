// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PaintingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API APaintingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage) override;

	void Save();
	void Load();

	UFUNCTION(BlueprintCallable)
	void SetStartLocation(FVector NewStartLocation);
	UFUNCTION(BlueprintCallable)
	FVector GetStartLocation();

	UFUNCTION(BlueprintCallable)
	void SetHoops(int32 NewHoops);
	UFUNCTION(BlueprintCallable)
	int32 GetHoops();

	UFUNCTION(BlueprintCallable)
	int32 GetRequiredHoops() {return RequiredHoops;}
	UFUNCTION(BlueprintCallable)
	void SetRequiredHoops(int32 NewRequiredHoops) {RequiredHoops = NewRequiredHoops;}
	UFUNCTION(BlueprintCallable)
	bool IsRequiredHoops();


	UFUNCTION(BlueprintCallable)
	void SaveAndQuit();

protected:
	void BeginPlay() override;

private:
	// State
	FString SlotName;

	UPROPERTY(EditAnywhere);
	int32 RequiredHoops = 20;

};
