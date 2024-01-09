#ifndef _BOSS
#define _BOSS


#include<SFML/Graphics.hpp>
#include "Characters.h"
#include "Resources.h"
#include "Animations.h"
#include <optional>
#include <iostream>
class Boss :public Characters {
public:
	Boss();
	void move(const sf::Vector2f v);
	bool Die();
	void jump();
	void Draw(sf::RenderWindow& window);
	void DieFormat();
	void setIsJumping(const bool isit);
	sf::Sprite getSprite();
	sf::Vector2f getVelocity() const;
	void setVelocity(const sf::Vector2f v);
	void setPosition(sf::Vector2f v);
	float GetSpeed();
	void update(sf::Time deltaTime, sf::RenderWindow& window, const bool Gcollis, const sf::Vector2f whereTo);
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
	void DieTimerReset();
	int getDamage()const;
	void setDamage(int dmg);
	void setDieFormatPos();
	void setDied();
	bool getDied()const;
	int getDieSpriteCount()const;
	bool getCDIsReadyToFire();
	
	Direction HeadTo();

	//operator between two bosses
	Boss& operator=(const Boss& other) {
		if (this == &other) {
			return *this;
		}
		return *this;
	}
private:
	sf::Clock c,c2;

	sf::Time m_coolDownTimer = sf::seconds(5 +rand() % 6);
	bool m_whileSkill = false,
		m_readyToFire = false;
	sf::Texture m_texture = sf::Texture();
	bool m_died = false;
	int m_hp = 30, m_lives = 1, m_damage = 2;
	bool isJumping = false,
		m_isGoingDown = false;
	sf::Sprite m_sprite;
	Animations m_animation;
	Direction m_dir = Direction::Left;
	Direction m_headingLeftOrRight = Direction::Left;
	float movementSpeed = 150 + rand()% 150;
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	float m_dx = 0, m_dy = 0,
		jumpStartedFrom = 0;
	float BossGravity = 9.8f;
	sf::Clock m_timer;
	sf::Vector2f m_diePosVEc;
	int m_dieSpriteCounter = 0;
};
#endif
