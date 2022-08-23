// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PainterSaveGame.h"
#include "Stroke.generated.h"


UCLASS()
class LIGHTPAINTER_API AStroke : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStroke();

	void Update(FVector CursorLocation);

	FStrokeState SerializeToStruct() const;
	static AStroke* SpawnAndDeserializeFromStruct(UWorld* World, const FStrokeState& StrokeState);

private:

	FTransform GetNextSegmentTransform(FVector CursorCurrentLocation) const;
	FTransform GetNextJointTransform(FVector CursorCurrentLocation) const;
	FVector GetNextSegmentScale(FVector CursorCurrentLocation)const;
	FQuat GetNextSegmentRotation(FVector CursorCurrentLocation)const;
	FVector GetNextSegmentLocation(FVector CursorCurrentLocation)const;

	// Components
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	// Config
	UPROPERTY(EditDefaultsOnly)
	class UInstancedStaticMeshComponent* StrokeMeshes;

	UPROPERTY(EditDefaultsOnly)
	class UInstancedStaticMeshComponent* JointsMeshes;

	// State
	FVector PreviousCursorLocation;
	TArray<FVector> ControlPoints;

};
