// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

UCLASS()
class KRAZYKARTS_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateLocationFromVelocity(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	// The mass of the car (kg),
	UPROPERTY(EditAnywhere)
	float Mass = 1000;

	//The force applied to the car when the throttle is fully down (N).
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce = 10000;

	//Minimum radius of the car turning circle at full lock(m).
	UPROPERTY(EditAnywhere)
	float MinTurningRadius = 10;

	//Higher means more drag.
	UPROPERTY(EditAnywhere)
	float DragCoefficient = 16;

	//Higher means more Rolling Resistance
	UPROPERTY(EditAnywhere)
	float RollingResistanceCoefficient = 0.015;

	FVector GetAirResistance();
	FVector GetRollingResistance();

	void ApplyRotation(float DeltaTime);

	void MoveForward(float Value);
	void MoveRight(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveForward(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveRight(float Value);

	FVector Velocity;

	float Throttle;
	float SteeringThrow;
};
