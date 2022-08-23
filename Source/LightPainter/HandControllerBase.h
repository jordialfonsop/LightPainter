// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandControllerBase.generated.h"

UCLASS()
class LIGHTPAINTER_API AHandControllerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandControllerBase();

	virtual void TriggerPressed() {}
	virtual void TriggerReleased() {}

	void SetHand(EControllerHand Hand);
	void PairController(AHandControllerBase* Controller);

	void Grip();
	void Release();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	UPROPERTY(VisibleAnywhere)
	class UMotionControllerComponent* MotionController;

	UPROPERTY(EditDefaultsOnly)
	class UHapticFeedbackEffect_Base* HapticEffect;

	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	bool CanClimb() const;

	bool bCanClimb = false;
	bool bIsClimbing = false;
	FVector ClimbingStartLocation;

	AHandControllerBase* OtherController;

};
