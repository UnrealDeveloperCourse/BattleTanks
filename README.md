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
### 3rd Person Camera Control

### User Interface (UI) in Unreal
### Main Menu Screens
### UI Scale Box, Buttons & Mouse
### Controller Ready Navigation

- MainMenu_BP Viewport
	+ Start Button widget
		* Events
			- OnClicked
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

- 

### Using Virtual and Override
### Overloading and Polymorphism
### Virtual Functions and Vtables
### Creating an AI Controller Class
### Get the Player Controller with C++
### Add `Tick()` to Player Controller
### Creating an Out Parameter Method
### Finding Screen Pixel Coordinates
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

