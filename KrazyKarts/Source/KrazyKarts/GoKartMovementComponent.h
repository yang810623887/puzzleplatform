// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	float Throttle;

	UPROPERTY()
	float SteeringThrow;

	UPROPERTY()
	float DeltaTime;

	UPROPERTY()
	float Time;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SimulateMove(const FGoKartMove& Move);

	FGoKartMove CreateMove(float DeltaTime);

	FVector GetVelocity() { return Velocity; }
	void SetVelocity(FVector Value) { Velocity = Value; }
	void SetThrottle(float Value) { Throttle = Value; }
	void SetSteeringThrow(float Value) { SteeringThrow = Value; }

	FGoKartMove GetLastMove() { return LastMove; }

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

	void UpdateLocationFromVelocity(float DeltaTime);

	FVector GetAirResistance();
	FVector GetRollingResistance();

	void ApplyRotation(float DeltaTime, float SteeringThrow);

	FVector Velocity;
	float Throttle;
	float SteeringThrow;
	FGoKartMove LastMove;
};
