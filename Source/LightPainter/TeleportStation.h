// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportStation.generated.h"

UCLASS()
class LIGHTPAINTER_API ATeleportStation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportStation();

	UFUNCTION(BlueprintCallable)
	FVector GetDestination();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Teleport;

	UPROPERTY()
	class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	FVector Destination;

};
