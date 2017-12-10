// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshSocket.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


// Forward Declaration
class UTankBarrel;


// Holds Barrel Properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation, float LaunchSpeed);

	void SetBarrelReference(UTankBarrel * BarrelToSet);

	void SetTurretReference(UStaticMeshComponent * TurretToSet);

private:

	UTankBarrel * Barrel = nullptr;

	UStaticMeshComponent * Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
};
