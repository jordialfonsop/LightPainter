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

	void PaginateRight();
	void PaginateLeft();
	void UpdateCurrentPage(int32 Offset);

	bool FindTeleportDestination(TArray<FVector> &OutPath, FVector& OutLocation);
	void UpdateDestinationMarker();
	void UpdateSpline(const TArray<FVector> &Path);
	void UpdateBlinkers();
	void DrawTeleportPath(const TArray<FVector> &Path);

	void BeginTeleport();
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

	UPROPERTY(VisibleAnywhere)
	class USplineComponent* TeleportPath;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMesh* TeleportMesh;
	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* TeleportMaterial;
	UPROPERTY()
	TArray<class USplineMeshComponent*> TeleportPathMeshPool;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> RightHandControllerClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> LeftHandControllerClass;
	UPROPERTY(EditDefaultsOnly)
	float PaginationThumbstickThreshold = 0.9;

	UPROPERTY()
	class UPostProcessComponent* Blinker;
	UPROPERTY()
	class UMaterialInstanceDynamic* BlinkerMaterial;
	UPROPERTY(EditAnywhere)
	class UMaterialInterface* BlinkerMaterialBase;

	UPROPERTY(EditAnywhere)
	class UCurveFloat* RadiusVelocity;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* DestinationMarker;

	FVector DestinationPoint;

	UPROPERTY(EditAnywhere)
	float DestinationMarkerSpeed = 1000.0f;

	UPROPERTY(EditAnywhere)
	float FadeTime = 1.0f;

	UPROPERTY(EditAnywhere)
	float RadiusValue = 0.6f;

	UPROPERTY(EditAnywhere)
	FVector TeleportProjectionExtent = FVector(100,100,100);

	// State
	int32 LastPaginationOffset = 0;

};
