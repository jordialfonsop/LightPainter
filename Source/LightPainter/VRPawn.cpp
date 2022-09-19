// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "NavigationSystem.h"
#include "HandControllerBase.h"
#include "PaintBrushHandController.h"
#include "UIPointerHandController.h"
#include "TimerManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "MotionControllerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PainterSaveGame.h"
#include "PaintingGameMode.h"
#include "PaintingPicker.h"
#include "EngineUtils.h"

// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VR Root"));
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);


}

class AHandControllerBase* AVRPawn::GetLeftController()
{
	return LeftController;
}

class AHandControllerBase* AVRPawn::GetRightController()
{
	return RightController;
}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if(RightHandControllerClass != nullptr && LeftHandControllerClass != nullptr){

		LeftController = GetWorld()->SpawnActor<AHandControllerBase>(LeftHandControllerClass);
		if (LeftController != nullptr){
			LeftController->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
			LeftController->SetOwner(this);
			LeftController->SetHand(EControllerHand::Left);
		}

		RightController = GetWorld()->SpawnActor<AHandControllerBase>(RightHandControllerClass);
		if (RightController != nullptr){
			RightController->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
			RightController->SetOwner(this);
			RightController->SetHand(EControllerHand::Right);
		}

		LeftController->PairController(RightController);

	}
	
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewCameraOffset = Camera->GetComponentLocation() - GetActorLocation();
	NewCameraOffset.Z = 0;
	AddActorWorldOffset(NewCameraOffset);
	VRRoot->AddWorldOffset(-NewCameraOffset);
	
}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&AVRPawn::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this,&AVRPawn::MoveRight);

	PlayerInputComponent->BindAction(TEXT("GripLeft"),EInputEvent::IE_Pressed,this,&AVRPawn::GripLeft);
	PlayerInputComponent->BindAction(TEXT("GripLeft"),EInputEvent::IE_Released,this,&AVRPawn::ReleaseLeft);
	PlayerInputComponent->BindAction(TEXT("GripRight"),EInputEvent::IE_Pressed,this,&AVRPawn::GripRight);
	PlayerInputComponent->BindAction(TEXT("GripRight"),EInputEvent::IE_Released,this,&AVRPawn::ReleaseRight);

	PlayerInputComponent->BindAction(TEXT("Trigger"),EInputEvent::IE_Pressed,this,&AVRPawn::TriggerPressed);
	PlayerInputComponent->BindAction(TEXT("Trigger"),EInputEvent::IE_Released,this,&AVRPawn::TriggerReleased);

	PlayerInputComponent->BindAction(TEXT("ToggleMenu"),EInputEvent::IE_Pressed,this,&AVRPawn::TogglePressed);

	PlayerInputComponent->BindAction(TEXT("PaginateRight"),EInputEvent::IE_Pressed, this, &AVRPawn::PaginateRight);
	PlayerInputComponent->BindAction(TEXT("PaginateLeft"),EInputEvent::IE_Pressed, this, &AVRPawn::PaginateLeft);

}

void AVRPawn::PaginateRight()
{
	UpdateCurrentPage(1.0);
}

void AVRPawn::PaginateLeft()
{
	UpdateCurrentPage(-1.0);
}


void AVRPawn::UpdateCurrentPage(int32 Offset)
{
	for (TActorIterator<APaintingPicker> PaintingPickerItr(GetWorld()); PaintingPickerItr; ++PaintingPickerItr)
	{
		PaintingPickerItr->UpdateCurrentPage(Offset);
	}
}

void AVRPawn::MoveUp(float AxisValue)
{
	AddMovementInput(Camera->GetForwardVector() * AxisValue);
}

void AVRPawn::MoveRight(float AxisValue)
{
	AddMovementInput(Camera->GetRightVector() * AxisValue);
}

void AVRPawn::GripLeft()
{
	LeftController->Grip();
}

void AVRPawn::ReleaseLeft()
{
	LeftController->Release();
}

void AVRPawn::GripRight()
{
	RightController->Grip();
}

void AVRPawn::ReleaseRight()
{
	RightController->Release();
}

void AVRPawn::TriggerPressed()
{
	RightController->TriggerPressed();
}

void AVRPawn::TriggerReleased()
{
	RightController->TriggerReleased();
}

void AVRPawn::TogglePressed()
{
	LeftController->ToggleMenuPressed();
}

void AVRPawn::BeginTeleport(FVector Point)
{
	DestinationPoint = Point;
	//Set Timer for FadeTime seconds
	FTimerHandle FadeTimer;
	GetWorldTimerManager().SetTimer(FadeTimer,this,&AVRPawn::FinishTeleport,FadeTime);

	//Fade Camera to Black
	StartFade(0,1);

}

void AVRPawn::FinishTeleport()
{
	
	//Teleport to Location
	FVector Destination = DestinationPoint + GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * GetActorUpVector();
	SetActorLocation(Destination);

	//Fade Back In
	StartFade(1,0);

}

void AVRPawn::StartFade(float FromAlpha, float ToAlpha)
{
	//Get Player Controller
	APlayerController* Player = Cast<APlayerController>(GetController());
	
	if (Player != nullptr){
		Player->PlayerCameraManager->StartCameraFade(FromAlpha,ToAlpha,FadeTime,FLinearColor::Black,false,true);
	}

}

