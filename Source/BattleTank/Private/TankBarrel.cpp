// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Need to clamp RelativeSpeed for values being passed in such as "5"
	auto RelativeSpeedClamped = FMath::Clamp<float>(RelativeSpeed, -1., 1.);

	auto ElevationChange = RelativeSpeedClamped * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewElevationUnclamped = RelativeRotation.Pitch + ElevationChange;
	
	// Make sure the values are clamped so the new elevation does not exceed max elevation
	
	// Static method FMath::Clamp()
	auto Elevation = FMath::Clamp<float>(NewElevationUnclamped, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}


