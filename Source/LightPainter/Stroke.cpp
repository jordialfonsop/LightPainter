// Fill out your copyright notice in the Description page of Project Settings.


#include "Stroke.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
AStroke::AStroke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StrokeMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("StrokeMeshes"));
	StrokeMeshes->SetupAttachment(Root);

	JointsMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("JointMeshes"));
	JointsMeshes->SetupAttachment(Root);

}

void AStroke::Update(FVector CursorLocation)
{
	if(PreviousCursorLocation.IsNearlyZero()){
		PreviousCursorLocation = CursorLocation;
		return;
	}

	StrokeMeshes->AddInstance(GetNextSegmentTransform(CursorLocation));
	JointsMeshes->AddInstance(GetNextJointTransform(CursorLocation));

	PreviousCursorLocation = CursorLocation;

}

FTransform AStroke::GetNextSegmentTransform(FVector CursorCurrentLocation) const
{
	FTransform SegmentTransform;

	SegmentTransform.SetScale3D(GetNextSegmentScale(CursorCurrentLocation));
	SegmentTransform.SetRotation(GetNextSegmentRotation(CursorCurrentLocation));
	SegmentTransform.SetLocation(GetNextSegmentLocation(CursorCurrentLocation));

	return SegmentTransform;
}

FTransform AStroke::GetNextJointTransform(FVector CurrentLocation) const
{
	FTransform JointTransform;
	JointTransform.SetLocation(GetTransform().InverseTransformPosition(CurrentLocation));
	return JointTransform;
}

FVector AStroke::GetNextSegmentScale(FVector CursorCurrentLocation) const
{
	FVector Segment = CursorCurrentLocation - PreviousCursorLocation;
	return FVector(Segment.Size(),1,1);
}

FQuat AStroke::GetNextSegmentRotation(FVector CursorCurrentLocation) const
{
	FVector Segment = CursorCurrentLocation - PreviousCursorLocation;
	return FQuat::FindBetweenNormals(FVector::ForwardVector,Segment.GetSafeNormal());
}

FVector AStroke::GetNextSegmentLocation(FVector CursorCurrentLocation) const
{
	return GetTransform().InverseTransformPosition(PreviousCursorLocation);
}

