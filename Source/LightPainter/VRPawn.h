// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRPawn.generated.h"

UCLASS()
class LIGHTPAINTER_API AVRPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRPawn();

	UFUNCTION(BlueprintCallable)
	class AHandControllerBase* GetLeftController();

	UFUNCTION(BlueprintCallable)
	class AHandControllerBase* GetRightController();

	UFUNCTION(BlueprintCallable)
	void BeginTeleport(FVector Point);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveUp(float AxisValue);
	void MoveRight(float AxisValue);

	void GripLeft();
	void ReleaseLeft();
	void GripRight();
	void ReleaseRight();

	void TriggerPressed();
	void TriggerReleased();

	void TogglePressed();

	void PaginateRight();
	void PaginateLeft();
	void UpdateCurrentPage(int32 Offset);

	void FinishTeleport();

	void StartFade(float FromAlpha, float ToAlpha);

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* Camera;
	UPROPERTY()
	class AHandControllerBase* LeftController;
	UPROPERTY()
	class AHandControllerBase* RightController;
	UPROPERTY()
	class USceneComponent* VRRoot;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> RightHandControllerClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> LeftHandControllerClass;
	UPROPERTY(EditDefaultsOnly)
	float PaginationThumbstickThreshold = 0.9;

	FVector DestinationPoint;

	UPROPERTY(EditAnywhere)
	float FadeTime = 1.0f;

	// State
	int32 LastPaginationOffset = 0;

};
