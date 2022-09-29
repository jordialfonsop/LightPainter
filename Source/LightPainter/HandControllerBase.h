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
	virtual void ToggleMenuPressed() {}

	void SetHand(EControllerHand Hand);
	void PairController(AHandControllerBase* Controller);

	void Grip();
	void Release();

	UFUNCTION(BlueprintCallable)
	class UMotionControllerComponent* GetMotionController();

	UFUNCTION(BlueprintCallable)
	AHandControllerBase* GetOtherController();

	UFUNCTION(BlueprintCallable)
	bool GetIsGrabbing() {return bIsGrabbing;}

	UFUNCTION(BlueprintCallable)
	bool GetCanGrab() {return bCanGrab;}

	UFUNCTION(BlueprintCallable)
	bool GetGrabActorReset() {return GrabActorReset;}

	UFUNCTION(BlueprintCallable)
	void SetGrabActorReset(bool NewGrabActorReset){ GrabActorReset = NewGrabActorReset;}

	UFUNCTION(BlueprintCallable)
	AActor* GetGrabActor() {return GrabActor;}

	UFUNCTION(BlueprintCallable)
	void SetGrabActor(AActor* NewGrabActor){ GrabActor = NewGrabActor;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	UPROPERTY(VisibleAnywhere)
	class UMotionControllerComponent* MotionController;

	UPROPERTY(EditDefaultsOnly)
	class UHapticFeedbackEffect_Base* HapticEffectClimb;

	UPROPERTY(EditDefaultsOnly)
	class UHapticFeedbackEffect_Base* HapticEffectGrab;

	

	bool CanClimb() const;
	bool CanGrab();

	bool bCanClimb = false;
	bool bIsClimbing = false;
	FVector ClimbingStartLocation;

	bool bCanGrab = false;
	bool bIsGrabbing = false;
	bool GrabActorReset = false;

	AActor* GrabActor;

	AHandControllerBase* OtherController;

};
