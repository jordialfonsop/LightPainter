// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintBrushHandController.h"
#include "Stroke.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
APaintBrushHandController::APaintBrushHandController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APaintBrushHandController::BeginPlay()
{
	Super::BeginPlay();

}

void APaintBrushHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentStroke)
	{
		CurrentStroke->Update(Location);
	}
}

void APaintBrushHandController::TriggerPressed()
{
	if(!deleteMode){
		CurrentStroke = GetWorld()->SpawnActor<AStroke>(StrokeClass);
		CurrentStroke->SetActorLocation(Location);
	}else{
		deleting = true;
	}
	
}

void APaintBrushHandController::TriggerReleased()
{
	CurrentStroke = nullptr;
	deleting = false;
}

void APaintBrushHandController::ToggleDeleteMode()
{
	deleteMode = !deleteMode;
}

void APaintBrushHandController::SetLocation(FVector Cone)
{
	Location = Cone;
}

void APaintBrushHandController::SetStrokeClass(TSubclassOf<class AStroke> Class)
{
	StrokeClass = Class;
}

bool APaintBrushHandController::GetDeleteMode()
{
	return deleteMode;
}

bool APaintBrushHandController::GetDeleting()
{
	return deleting;
}

TSubclassOf<class AStroke> APaintBrushHandController::GetStrokeClass()
{
	return StrokeClass;
}

void APaintBrushHandController::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor,OtherActor);
	if(deleting){
		TArray<AActor*> OverlappingActors;
		GetOverlappingActors(OverlappingActors);
		for (int32 i =0; i < OverlappingActors.Num();i++){
			if (OverlappingActors[i]->ActorHasTag(TEXT("Stroke"))){
				UGameplayStatics::PlaySoundAtLocation(GetWorld(),DeleteSound,GetActorLocation());
				OverlappingActors[i]->Destroy();
			};
		}
	}
	

}


