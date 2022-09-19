// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportStation.h"

// Sets default values
ATeleportStation::ATeleportStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetupAttachment(GetRootComponent());

	Teleport = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Teleport"));
	Teleport->SetupAttachment(Root);

}

FVector ATeleportStation::GetDestination()
{
	return Destination;
}

// Called when the game starts or when spawned
void ATeleportStation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

