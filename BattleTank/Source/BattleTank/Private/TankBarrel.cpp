// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto RelativeSpeedClamped = FMath::Clamp<float>(RelativeSpeed, -1., 1.);
	auto ElevationChange = RelativeSpeedClamped * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewElevationUnclamped = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(NewElevationUnclamped, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}


