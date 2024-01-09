#ifndef _FORK
#define _FORK

#include<SFML/Graphics.hpp>
#include "Characters.h"
#include "Resources.h"
#include "Animations.h"
#include <optional>
#include <iostream>

//class ForkEnemy that enheritance frrom characters class
class ForkEnemy : public Characters{
public:
	ForkEnemy();
	bool Die();
	void move(sf::Vector2f vec);
	void DieFormat();
	sf::Sprite getSprite() ;
	sf::Vector2f getVelocity() const;
	void setVelocity(const sf::Vector2f v);
	void setPosition(sf::Vector2f v);
	float GetSpeed();
	void update(sf::Time deltaTime, sf::RenderWindow& window,const bool Gcollis, const sf::Vector2f whereTo);
	void HandleInput(sf::RenderWindow& window, const sf::Vector2f whereTo);
	bool CheckGroundCollision();
	bool getIfGoingDown();
	void direction(sf::Keyboard::Key key);
	Direction getDir();
	void setAnimationByDirection(Direction dir);
	void setHp();
	void LostHp(int GunDamage);
	int GetHp();
	void LostLife();
	int GetLives();
	void setDamage(int dmg);
	int getDamage()const;
	void setDied();
	bool getDied()const;

	//operator between two forks
	ForkEnemy& operator=(const ForkEnemy& other) {
		if (this == &other) {
			return *this;
		}
		return *this;
	}

private:
	sf::Texture m_texture = sf::Texture(), 
		m_dieTexture = sf::Texture();
	bool m_died = false;
	int m_hp = 1, m_lives = 1,m_damage = 1;
	sf::Sprite m_sprite;
	Animations m_animation;
	Direction m_dir = Direction::Left;
	float movementSpeed = 450.f;
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	float m_dy = 0;
	float m_Gravity = 9.8f;
	bool m_isGoingDown;

};

#endif