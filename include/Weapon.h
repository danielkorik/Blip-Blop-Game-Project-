#ifndef _WEAPON
#define _WEAPON

#include<SFML/Graphics.hpp>
#include"Animations.h"

//~Weapon class that is polymorphisem
class Weapon {
public:
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void setDamage() = 0;
	virtual int getDamage() = 0;
	virtual void update(sf::Time deltaTime) = 0;
	virtual sf::Sprite &GetBulletSprite() = 0;
	virtual void SetPosition(sf::Sprite p) = 0;
	virtual bool isOutOFAmmo()=0;
	virtual void setTexture(Direction dir) = 0;
	virtual void setVelocity(sf::Vector2f vec) = 0;
	virtual void SetSpritesPos() = 0;
};

#endif