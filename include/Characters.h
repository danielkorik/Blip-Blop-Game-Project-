#ifndef _CHARACTERS
#define _CHARACTERS

#include<SFML/Graphics.hpp>
#include"Direction.h"

// its a class that used for polymorphisem
class Characters{
public:

	virtual void setPosition(sf::Vector2f v) = 0;	//set postion
	virtual void move(sf::Vector2f vec) = 0;	//move
	virtual bool Die() = 0;	//die function
	virtual float GetSpeed() = 0;	//getting the speed 
	virtual void update(sf::Time deltaTime, sf::RenderWindow& window, const bool Gcollis, const sf::Vector2f whereTo) = 0;	//update
	virtual void HandleInput(sf::RenderWindow& window, const sf::Vector2f whereTo) = 0;	//handle the inputs of the user
	virtual sf::Sprite getSprite() = 0;	//getting the sprite
	virtual bool getIfGoingDown() = 0;	//get if falling
	virtual void direction(sf::Keyboard::Key key) = 0;	//check direction key
	virtual Direction getDir() = 0;	//get direcction
	virtual void setAnimationByDirection(Direction dir) = 0;	//set texture 
	virtual void setHp() = 0;	//set hp
	virtual void LostHp(int GunDamage) = 0;	//lose hp
	virtual int GetHp() = 0;	//get the hp
	virtual void LostLife()= 0;	//lostlife
	virtual int GetLives()= 0;	//get the lifes
};
#endif


