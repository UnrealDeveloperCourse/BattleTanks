# Section_04
Battle Tank

### Intro, Notes & Section 4 Assets


### Battle Tank Overview


### Game Design Document

- Concept, Rulese and Initial Requirements
- Iterate, ask what is least fun
- We aren't AAA studios
- World of Tanks

- Concepts
	+ Head to head combat game
- Rules
	+ Move anywhere in the terrain surrounded by mountains
	+ Both players infinite health and ammo
	+ Each direct hit takes away healt
	+ Last player standing wins
- Requirements (Assets)
	+ SFX: Gun fire, explosion, barrel moving, turret moving, engine sound
	+ Static Mesh: Simple tank, tracks, body, turret, barrel
	+ Textures
	+ Music

- Iterative cycle
	+ World -> Tank -> Controls -> Player 2 (human or AI) -> UI -> World


### Setting Up a GitHub Repo

- default UnrealEngine .gitignore

### Creating & Deleting Landscapes
### Landscape Setup & Scaling
### A Landscaping Process
### Upgrading Engine Version
### Using Landscape Layers
### Flat Shading Low Poly Landscapes
### More Landscaping Tools

### Mid-Section Quiz

### Tank Control System
### Actors from Multiple Meshes
### Configuring a Tank

- Viewport -> Blueprints -> World Override -> Game Mode -> Create -> BattleTankGameMode
- BattleTankGameMode_BP
- Default Pawn Class
- Tank_BP

### 3rd Person Camera Control

- Tank_BP Event Graph

![Camera Input Binding](BattleTank/Saved/Screenshots/Windows/Tank_BP_Event_Graph_Camera_Input_Binding.png)

### User Interface (UI) in Unreal

- Create Aiming reticule
- Create Widget Blueprint called PlayerUI_BP
	+ Create a test image
	+ Edit scale and position of the reticule
- Create a Player Controller Blueprint class
	+ TankPlayerController_BP
- TankPlayerController_BP Event Graph
	+ Event BeginPlay
	+ Create Widget with class PlayerUI_BP
	+ Add to Viewport

![PlayerUI_BP Event Graph](BattleTank/Saved/Screenshots/Windows/PlayerUI_BP_Event_Graph.png)

- Make the reticule visible
	+ BattleTankGameMode_BP
	+ Player Controller Class
		* TankPlayerController_BP

### Main Menu Screens

- Create a new level called MainMenu Level
- Create Widget Blueprint called MainMenu_BP
	+ edit and add a quick test image
- Edit the MainMenu Level BP
	+ Event BeginPlay
	+ Create Widget
		* to display start screen image
	+ Add to Viewport
- Apply a background image

![MainMenu Level BP Viewport Widget](BattleTank/Saved/Screenshots/Windows/MainMenu_Level_BP_ViewportWidget.png)

![MainMenu_BP Viewport](BattleTank/Saved/Screenshots/Windows/MainMenu_BP_Viewport_Hierarchy.png)

### UI Scale Box, Buttons & Mouse

- MainMenu Level BP
- How to show the Player Mouse
- GetPlayerController
- SetShowMouseCursor

![MainMenu Level BP](BattleTank/Saved/Screenshots/Windows/MainMenu_Level_BP.png)

### Controller Ready Navigation

- MainMenu_BP Viewport
	+ Start Button widget
		* Events
			- OnClicked

![MainMenu_BP Viewport](BattleTank/Saved/Screenshots/Windows/MainMenu_BP_Viewport.png)

- MainMenu_BP Event Graph
	+ Wire up opening a level
		* OpenLevel node
	+ Focus the Start Button automatically
		* WidgetReady
- MainMenu Level BP
	+ Wire up WidgetReady event at the end of the control graph
- MainMenu_BP Event Graph
	+ create Start Button node
	+ create Get Player Controller node
	+ create Set Input Mode UIOnly node

![MainMenu_BP Event Graph](BattleTank/Saved/Screenshots/Windows/MainMenu_BP_Event_Graph.png)

- Create a Game Quit Action
- Project -> Engine Input -> Action Mapping
	+ Game Pad Special Left Button
		* The back button on an XBox controller
- BattleGround Level BP
	+ Wire up Action Quit

![BattleGround Level BP Event Graph](BattleTank/Saved/Screenshots/Windows/BattleGround_Level_BP.png)

### Trial Packaging Your Game

- Project Settings -> Maps and Modes
	+ Game Default Map
	+ Editor Startup Map
- File -> Package Project -> Windows 64 bit
- Problem: Set Input Mode UIOnly
	+ Mode never switches over to Game Only

### Mid Section Quiz

### Delegating to Components

- Create a Tank C++ Class

![Create a Tank C++ Class](BattleTank/Saved/Screenshots/Windows/Tank_Class.png)

- Create a TankPlayerController C++ Class

![Reparent Player Controller Class](BattleTank/Saved/Screenshots/Windows/Class_Settings_ReParent_Controller_Class.png)

### Using Virtual and Override

- Backstory: what pawn are we possessing when starting the game?
- Try Logging from a Blueprint

![Print Player Controller](BattleTank/Saved/Screenshots/Windows/Print_Player_Controller.png)

- Take a look at APlayerController and the AActor parent

[APlayerController Unreal Doc](https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/APlayerController/index.html)

- `virtual void BeginPlay()`
- need to override, what is the syntax?
- `void BeginPlay() override;`
- `virtual` ancestors are allowed to override
- in implementation `Super::BeginPlay()`
- Same setup in Tank boilerplate code

### Overloading and Polymorphism

- Polymorphism
	+ Ad-hoc = A different implementation per signature, same signature different implementation
	+ Subtype = Parent pointers pointing at children instances
	+ Parametric = One implementation, multiple signatures
	+ [Blog about cpp polymorphism](http://www.catonmat.net/blog/cpp-polymorphism/)

### Virtual Functions and Vtables

- [Compiler Explorer](https://godbolt.org/)
- [YT video](https://www.youtube.com/watch?v=bSkpMdDe4g4)
- Assembly code and a view for Binary instructions!
- Find out just how many more lines of Assembly virual will take
- Assembly code methods are labels
- Experiment by removing `virtual` + overrides
	+ Observations
	+ code is shorter
	+ `animal.MakeNoise()`
		* right click on the line, scroll to assembly
		* Assembly is actually only one line of code
		* it is actually an address in memory (400cf4)

- virtual
- Vtable lookup the address of MakeNoise function for the type of animal
	+ Animal -> Cat Vtable -> Cat::MakeNoise()
	+ Animal -> Dog Vtable -> Dog::MakeNoise()
	+ If another Cat then share the same Cat Vtable
- insert virtual back into the source code

```cpp
// 2. subtype polymorphism (AKA runtime polymorphism)
class Animal
{
public:
	virtual void MakeNoise()
	{
		std::cout << "???" << std::endl;
	}
};
```

- notice vtable in assembly

```
vtable for Kitteh:
  .quad 0
  .quad typeinfo for Kitteh
  .quad Kitteh::MakeNoise()
```

- more 'hops' involved when using virtual
- cpp mantra "don't pay for what you don't use"

### Creating an AI Controller Class

![Aiming Architecture](BattleTank/Saved/Screenshots/Windows/Aiming_Architecture_01.png)

![AI Controller C++ Class](BattleTank/Saved/Screenshots/Windows/AI_Controller_Cpp_Class.png)

- Create a TankAIController
- Auto Possess [with] AI

![AI Auto Possess](BattleTank/Saved/Screenshots/Windows/Tank_BP_AI_AutoPossess.png)

- At Game Start multiple pawns get possessed by TankAIController

![TankAIController Start Game](BattleTank/Saved/Screenshots/Windows/Tank_AIController_StartGame.png)

### Get the Player Controller with C++

- AimAt(Player)

![Aiming Architecture](BattleTank/Saved/Screenshots/Windows/Aiming_Architecture_02.png)

![Finding Player Controller](BattleTank/Saved/Screenshots/Windows/Finding_Player_Controller.png)

```cpp
ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn){ return PlayerPawn; }
	return Cast<ATank>(PlayerPawn);
}
```

![GetPlayerTank](BattleTank/Saved/Screenshots/Windows/GetPlayerTank.png)

### Add `Tick()` to Player Controller

- AimAt(Crosshair)

![Aiming Architecture](BattleTank/Saved/Screenshots/Windows/Aiming_Architecture_03.png)

```cpp
void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank()) { return; }

	// Get world location of linetrace through crosshair
	// If it hits the landscape
		// Tell controlled tank to aim at this point
}
```

### Creating an Out Parameter Method

```cpp
// Get world location of linetrace through crosshair, true if hits landscape
bool GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	return true;
}
```

### Finding Screen Pixel Coordinates

- **Objective**: Find crosshair location on the screen

```cpp
/// TankPlayerController.h

// location left/right
UPROPERTY(EditAnywhere)
float CrosshairXLocation = 0.5;

// location from top down
UPROPERTY(EditAnywhere)
float CrosshairYLocation = 0.3333;
```

```cpp
/// TankPlayerController.cpp

// Find crosshair location
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
```

### Using `DeprojectScreenToWorld`

- **Objective**: Get world space direction as a unit vector

![DeprojectScreenToWorld UE_Log](BattleTank/Saved/Screenshots/Windows/UE_Log_DeprojectScreenToWorld.png)

- [DeprojectScreenPositionToWorld Unreal Doc](https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/APlayerController/DeprojectScreenPositionToWorld/index.html)

```cpp
/// TankPlayerController.h

bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
```

```cpp
/// TankPlayerController.cpp

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector CameraWorldLocation; // TODO: discard
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}
```

### Using `LineTraceSingleByChannel`

- **Objective**: Get an actual point in the world to aim at
 
![LinearTraceSingleByChannel UE_Log](BattleTank/Saved/Screenshots/Windows/UE_Log_LinearTraceSingleByChannel.png)

- [LineTraceSingleByChannel Unreal Doc](https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Engine/UWorld/LineTraceSingleByChannel/index.html)

```cpp
/// TankPlayerController.h

UPROPERTY(EditAnywhere)
float LineTraceRange = 1000000;

bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
```

```cpp
/// TankPlayerController.cpp

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	
	return false;
}
```

### Unify Player and AI Aiming

- **Objective**: Call same `AimAt()` method whether it is a player controller or an AI controller possessing a tank

![Aiming Architecture](BattleTank/Saved/Screenshots/Windows/Aiming_Architecture_04.png)

- Create `AimAt` method on the Tank class

```cpp
/// Tank.h

public:
	void AimAt(FVector HitLocation);
```

```cpp
/// Tank.cpp

void ATank::AimAt(FVector HitLocation)
{
	auto OurTankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *HitLocation.ToString())
}
```

- Call the method from the player controller

```cpp
/// TankPlayerController.cpp

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}
```

- Add a `Tick` method, call same `AimAt` method every frame to aim at the player

```cpp
/// TankAIController.h

private:
	virtual void Tick(float DeltaTime) override;
```

```cpp
/// TankAIController.cpp

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		// Move towards the player
		
		// Aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire when ready
	}
}
```

- Using the same `AimAt` method is automatically equitable game play, fair, and balanced.


### Mid Section Quiz

### Creating Default Sub Objects in C++

- **Objective**: Create an Aiming Component in C++ and Delegate aiming to it

![Aiming Architecture](BattleTank/Saved/Screenshots/Windows/Aiming_Architecture_05.png)

1. Create the Aiming Component Default Subobject and add it to the Tank

```cpp
/// Tank.h

// Create in UnrealEd and hash include this Actor Component
#include "TankAimingComponent.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Aiming code

protected:
	// Cannot make private, would cause compile error and shouldn't be public
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Private code
}
```

```cpp
/// Tank.cpp

ATank::ATank()
{
 	// Tick code

	// Pointer protection not needed since created during construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}
```

2. Delegate `AimAt()` to the Aiming Component instead of Tank

```cpp
/// TankAimingComponent.h

// Macro Boilerplate code
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Boilerplate code

	// Tick Component code

	void AimAt(FVector HitLocation);
}

```

```cpp
/// TankAimingComponent.cpp

void UTankAimingComponent::AimAt(FVector HitLocation)
{	
	// `GetOwner()` grab the parent's name, just `GetName()` when implemented in Tank.cpp
	auto OurTankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *HitLocation.ToString())
}
```

3. Call the method on the `TankAimingComponent`

```cpp
/// Tank.cpp

// Much simpler `AimAt` method delegated to the component
void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation);
}
```

### `BlueprintCallable()`

- **Objective**: Find start and end location of the projectile

![Barrel -> HitLocation](BattleTank/Saved/Screenshots/Windows/BP_Callable_Barrel_HitLocation.png)

![Class Viewer Static Mesh Component](BattleTank/Saved/Screenshots/Windows/Class_Viewer_Static_Mesh_Component.png)

![TankBP Blueprint Callable Set Barrel Reference](BattleTank/Saved/Screenshots/Windows/TankBP_Blueprint_Callable.png)

1. Declare `SetBarrelReferenced`

```cpp
/// TankAimingComponent.h

#include "Components/StaticMeshComponent.h"

/// Macro here
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	/// Boilerplate here

public:	
	/// Other methods here

	// Method for setting the barrel reference
	void SetBarrelReference(UStaticMeshComponent * BarrelToSet);
protected:
	// protected code
private:
	// initialize default barrel pointer
	UStaticMeshComponent * Barrel = nullptr;
}
```

2. Implement `SetBarrelReference`

```cpp
/// TankAimingComponent.cpp

// implementation for setting the barrel reference
void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}
```

```cpp
/// Tank.h

/// Macro here
class BATTLETANK_API ATank : public APawn
{
	/// Boilerplate here
public:
	// Create a BlueprintCallable method
	UFUNCTION(BlueprintCallable, category=Setup)
	void SetBarrelReference(UStaticMeshComponent * BarrelToSet);
protected:
	// protected code
private:
	// private code
}
```

```cpp
/// Tank.cpp

// Delegate out setting the barrel reference
void ATank::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}
```

3. Logging out the Barrel Component Location

```cpp
/// TankAimingComponent.cpp

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	auto OurTankName = GetOwner()->GetName();
	// Now we can get the barrel component location
	auto BarrelLocation = Barrel->GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString())
}
```

### `SuggestProjectileVelocity()`

- **Objective**: Understand launch velocity

![Launch Unit Vectors](BattleTank/Saved/Screenshots/Windows/LaunchVelocity_UnitVectors.png)

[Wikipedia Projectile Motion](https://en.wikipedia.org/wiki/Projectile_motion)

![Wikipedia Projectile Motion Image](BattleTank/Saved/Downloads/Ideal_projectile_motion_for_different_angles.png)

[SuggestProjectileVelocity Learn Doc](https://docs.unrealengine.com/latest/INT/BlueprintAPI/Game/Components/ProjectileMovement/SuggestProjectileVelocity/index.html)

[SuggestProjectileVelocity C++ Doc](https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Kismet/UGameplayStatics/SuggestProjectileVelocity/index.html)

1. Setup a `LaunchSpeed` parameter

```cpp
/// Tank.h

/// Macros here
class BATTLETANK_API ATank : public APawn
{
	/// Boilerplate
public:
	// Tank doesn't care about `LaunchSpeed` or other firing parameters
	void AimAt(FVector HitLocation);
	// More code
protected:
	// Protected code
private:
	// Create a new property that will show up in a new
	// Firing category on the Blueprint which will 
	// allow us to experiment with different launch speeds
	UPROPERTY(EditAnywhere, category=Firing)
	float LaunchSpeed = 100000; // 1000 m/s
};

```

2. Pass the `LaunchSpeed` to `TankAimingComponent` `AimAt()`

```cpp
/// Tank.cpp

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}
```

3. Add the new parameter to the aiming component

```cpp
/// TankAimingComponent.h

/// Macro here
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	/// Boilerplate here
public:	
	void AimAt(FVector HitLocation, float LaunchSpeed);
protected:
	// protected code
private:
	// private code
}
```

4. Log out the `LaunchSpeed` parameter's value

```cpp
/// TankAimingComponent.cpp

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("Firing at %.2f cm/s"), LaunchSpeed)
}
```

### Predict Projectile Landing Point

- **Objective**:

### Using `FRotators` in Unreal

- **Objective**:

### The C++ Compilation Process

- **Objective**:

### Using Forward Declarations

- **Objective**:

### `BlueprintSpawnableComponent()`

- **Objective**:

### Review Our Execution Flow

- **Objective**:

### How to Report Bugs


- **Objective**:

### Mid-Section Quiz


- **Objective**:

### Using `Clamp()` to Limit Values

- **Objective**:

### CHALLENGE - Turret Rotation

- **Objective**:

### CHALLENGE - Turret Rotation Pt 2

- **Objective**:

### Setting Up Projectiles

- **Objective**:

### Upgrading to Unreal 4.2

- **Objective**:

### Working Around Awkward Bugs

- **Objective**:

### Using `SpawnActor<>()` to Spawn

- **Objective**:

### Projectile Moving Components

- **Objective**:

### Making AI Tanks Fire

- **Objective**:

### `EditAnywhere` vs `EditDefaultsOnly`


- **Objective**:

### Mid-Section Quiz


- **Objective**:

### Adding a Quit Button

- **Objective**:

### Setup Track Throttles

- **Objective**:

### `ApplyForceAtLocation()` in Action

- **Objective**:

### Physics Materials and Friction

- **Objective**:

### Fly-By-Wire Control System

- **Objective**:

### Using BluePrintReadOnly

- **Objective**:

### A Better Component Architecture

- **Objective**:

### Completing Manual Tank Movement

- **Objective**:

### Introducing AI Pathfinding

- **Objective**:

### Dissecting `RequestDirectMove()`


- **Objective**:

### Mid-Section Quiz


- **Objective**:

### DotProduct() Vector Operator

- **Objective**:

### CrossProduct() Vector Operator

- **Objective**:

### Finalizing Your Class Code

- **Objective**:

### How to Use Blueprint Variables

- **Objective**:

### Using Enum(erations) in UE4

- **Objective**:

### Refactoring our Aiming Component

- **Objective**:

### Attaching a Debugger to Unreal

- **Objective**:

### Constructor and Begin Play Timing

- **Objective**:

### Decoupling Your Architecture

- **Objective**:

### `BlueprintImplementableEvent`


- **Objective**:


- **Objective**:### Mid-Section Quiz

