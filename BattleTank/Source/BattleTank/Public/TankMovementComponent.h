// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


// Forward Declarations
class UTankTrack;


/**
 * Takes input axis values and uses them to move the tank
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	// Need to wire this up in Blueprint when the component is added
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);

	UPROPERTY(EditDefaultsOnly, category = Firing)
	float LaunchSpeed = 100000; // 1000 m/s
	
private:
	UTankTrack * LeftTrack = nullptr;
	UTankTrack * RightTrack = nullptr;

	// Used by AI pathfinding logic
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
