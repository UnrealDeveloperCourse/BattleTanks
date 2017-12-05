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

- First, find crosshair location on the screen

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
### Using `LineTraceSingleByChannel`
### Unify Player and AI Aiming

### Mid Section Quiz

### Creating Default Sub Objects in C++
### `BlueprintCallable()`
### `SuggestProjectileVelocity()`
### Predict Projectile Landing Point
### Using `FRotators` in Unreal
### The C++ Compilation Process
### Using Forward Declarations
### `BlueprintSpawnableComponent()`
### Review Our Execution Flow
### How to Report Bugs

### Mid-Section Quiz

### Using `Clamp()` to Limit Values
### CHALLENGE - Turret Rotation
### CHALLENGE - Turret Rotation Pt 2
### Setting Up Projectiles
### Upgrading to Unreal 4.2
### Working Around Awkward Bugs
### Using `SpawnActor<>()` to Spawn
### Projectile Moving Components
### Making AI Tanks Fire
### `EditAnywhere` vs `EditDefaultsOnly`

### Mid-Section Quiz

### 
### 
### 
### 

