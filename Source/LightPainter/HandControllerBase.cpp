// Fill out your copyright notice in the Description page of Project Settings.


#include "HandControllerBase.h"
#include "MotionControllerComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"

// Sets default values
AHandControllerBase::AHandControllerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(MotionController);

}

void AHandControllerBase::SetHand(EControllerHand Hand)
{
	MotionController->SetTrackingSource(Hand);
}

void AHandControllerBase::Grip()
{
	if(bCanClimb && !bIsClimbing){
		ClimbingStartLocation = GetActorLocation();
		bIsClimbing = true;

		OtherController->bIsClimbing = false;

		ACharacter* Character = Cast<ACharacter>(GetAttachParentActor());
		if (Character != nullptr)
		{
			Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		}
	}

	if(bCanGrab && !bIsGrabbing){

		bIsGrabbing = true;
		OtherController->bIsGrabbing = false;

	}
}

void AHandControllerBase::Release()
{
	if (bIsClimbing)
	{
		bIsClimbing = false;

		ACharacter* Character = Cast<ACharacter>(GetAttachParentActor());
		if (Character != nullptr)
		{
			Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
		}
	}

	if (bIsGrabbing)
	{
		bIsGrabbing = false;

	}
}

UMotionControllerComponent* AHandControllerBase::GetMotionController()
{
	return MotionController;
}

AHandControllerBase* AHandControllerBase::GetOtherController()
{
	return OtherController;
}

void AHandControllerBase::PairController(AHandControllerBase* Controller)
{
	OtherController = Controller;
	OtherController->OtherController = this;
} 

// Called when the game starts or when spawned
void AHandControllerBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this,&AHandControllerBase::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AHandControllerBase::ActorEndOverlap);

}

// Called every frame
void AHandControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsClimbing)
	{
		FVector HandControllerDelta = GetActorLocation() - ClimbingStartLocation;

		GetAttachParentActor()->AddActorWorldOffset(-HandControllerDelta);
	}
	
}

void AHandControllerBase::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	bool bNewCanClimb = CanClimb();
	if (!bCanClimb && bNewCanClimb)
	{
		APawn* Pawn = Cast<APawn>(GetAttachParentActor());
		if (Pawn != nullptr)
		{	
			APlayerController* Controller = Cast<APlayerController>(Pawn->GetController());
			if (Controller != nullptr)
			{
				Controller->PlayHapticEffect(HapticEffectClimb, MotionController->GetTrackingSource());
			}
		}
	}
	bCanClimb = bNewCanClimb;

	bool bNewCanGrab = CanGrab();
	if (!bCanGrab && bNewCanGrab)
	{
		APawn* Pawn = Cast<APawn>(GetAttachParentActor());
		if (Pawn != nullptr)
		{	
			APlayerController* Controller = Cast<APlayerController>(Pawn->GetController());
			if (Controller != nullptr)
			{
				Controller->PlayHapticEffect(HapticEffectGrab, MotionController->GetTrackingSource());
			}
		}
	}
	bCanGrab = bNewCanGrab;

}

void AHandControllerBase::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	bCanClimb = CanClimb();
	bCanGrab = CanGrab();
}

bool AHandControllerBase::CanClimb() const
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for (int32 i =0; i < OverlappingActors.Num();i++){
		if (OverlappingActors[i]->ActorHasTag(TEXT("Climbable"))){
			return true;
		};
	}

	return false;
	
}

bool AHandControllerBase::CanGrab()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for (int32 i =0; i < OverlappingActors.Num();i++){
		if (OverlappingActors[i]->ActorHasTag(TEXT("Grabbable"))){
			GrabActor = OverlappingActors[i];
			GrabActorReset = false;
			return true;
		};
	}
	GrabActor = nullptr;
	return false;
	
}
