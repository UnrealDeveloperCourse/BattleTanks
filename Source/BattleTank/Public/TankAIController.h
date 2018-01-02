// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// proximity the AI tank should achieve when moving towards player
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 6000; // todo check cm

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
