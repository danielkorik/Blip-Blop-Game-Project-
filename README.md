# Blip-and-Blop
Blip and Blop remake project
## A Bit About The Files.
## •	Main.cpp
  Calls for the Game class and just runs the Game.run() function
## •	AnimationData.h & AnimationData.cpp:
  Contains the code of the animations that makes sure to get the animation data from the resources class
## •	Animations.h & Animations.cpp :
  Class that gets us the texture and updates the textures from the unorderd map object that holds all the textures
## •	BlipAndBlop.h & BlipAndBlop.cpp :
  Class that holds and contains all the character game functions and its priority to get us the character ready from updates and inputs and keys and the move it holds functions to the jump and the velocity and   all the things needed for the player character
## •	Board.h & Board.cpp :
  Class that holds all the check collisions between the characters and the enemies
  And the collisions with the platforms of the game
## •	Boss.h && Boss.cpp:
  Class that contains all the boss enemy needed sets and updates and draws.

## •	BossBullet.h & BossBullet.cpp: 
  Class that sets the boss bullets and all the needed set of the boss bullets and damage and forcespeed and velocity and draw.

## •	Button.h & Button.cpp:
  Used to just set the buttons of the menu

## •	Characters.h :
  A class that been used for the enheritance all classes of enemies and the BlipAndBlop enheritance from it and it holds all the virtual functions

## •	DefaultWeap.h & DefaultWeap.cpp :
  Class that sets the default bullets of the BlipAndBlop and all the needed set of the default bullets and damage and forcespeed and velocity and draw.

## •	Direction.h && Direction.cpp :
  An enum class that holds the firections names and a functions to convert the direction to vector and the opposite

## •	ForkEnemy.h & ForkEnemy.cpp :
  A class that holds all the needed sets for the fork enemy,the damage the hp the update and the draw and others.

## •	Game.h & Game.cpp :
  The main class that holds all the game run and play and menu it’s the class that holds all the main and important things of the game it holds the functions that check collisions between the objects that it       holds like characters and enemies and the platforms it holds the update and draw functions and the bullets update and all the game needed sets

## •	Globals.h & Globals.cpp :
  A class that holds all the globals of the game.

## •	Platform.h & Platform.cpp :
  A class that reads the platforms points from the file and set the platform points.

## •	Resources.h & Resources.cpp :
  A class that holds the resources of the game .it contains an animationData vector that holds all the textures from the png sprites and it holds the music and sound functions of the game

## •	RifleWeap.h & RifleWeap.cpp :
  Class that sets the Rifle bullets of the BlipAndBlop and all the needed set of theRifle bullets and damage and forcespeed and velocity and draw.

## •	ShotgunWeap.h & ShotgunWeap.cpp :
  Class that sets the ShotGunWeapon bullets of the BlipAndBlop and all the needed set of the ShotGun Weapon bullets and damage and forcespeed and velocity and draw.

## •	Weapon.h & Weapon.cpp :
  Class that used for inheritance all the weapons inheritance  from it and it holds all the virtual functions .
## •	StandardEnemy.h & StandardEnemy.cpp :
	A class that holds all the needed sets for the standard enemy, the  damage the hp the update and the draw and others.

## •	StatusBar.h & StatusBar.cpp :
  Class that holds all the text of the status bar on the game like the hp sprite and the lives text
  And the score text and the game o ver or win text and etc.


