// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportStation.h"
#include "VRPawn.h"

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

	OnActorBeginOverlap.AddDynamic(this,&ATeleportStation::ActorBeginOverlap);
	
}

// Called every frame
void ATeleportStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleportStation::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for (int32 i =0; i < OverlappingActors.Num();i++){
		if (OverlappingActors[i]->ActorHasTag(TEXT("VRPawn"))){
			Cast<AVRPawn>(OverlappingActors[i])->BeginTeleport(Destination);
		};
	}
}

