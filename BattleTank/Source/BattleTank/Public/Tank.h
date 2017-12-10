// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


// Forward Declaration
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, category=Setup)
	void SetBarrelReference(UTankBarrel * BarrelToSet);

	UFUNCTION(BlueprintCallable, category = Setup)
	void SetTurretReference(UTankTurret * TurretToSet);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, category=Firing)
	float LaunchSpeed = 100000; // 1000 m/s
};
