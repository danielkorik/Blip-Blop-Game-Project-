#ifndef _BLIPANDBLOP
#define _BLIPANDBLOP



#include<SFML/Graphics.hpp>
#include"Globals.h"
#include<iostream>
#include"Animations.h"
#include"Characters.h"
#include"Board.h"
#include <utility>
//#include"DefaultWeap.h"

// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)


class BlipAndBlop :public Characters{
public:
	BlipAndBlop(Resources::Objects obj, Resources::Objects weap);
	void setPosition(sf::Vector2f v);
	void move(sf::Vector2f vec);
	bool Die();
	//void jump();
	//void setLives(int live);
	//void setPoints(int p);
	sf::Sprite getSprite();
	void setColor(sf::Color c);
	//int getLives();
	bool getIfGoingDown();
	void setIsGoingDown(const bool is);
	//int getPoints();
	void update(sf::Time deltaTime, sf::RenderWindow& window, /*sf::Clock clock,*/ const bool Gcollis/*,const Board& board ,*/, const sf::Vector2f whereTo);
	void HandleInput(sf::RenderWindow& window, const sf::Vector2f whereTo);
	float GetSpeed();
	void direction(sf::Keyboard::Key key);
	void setIsJumping(const bool isit);
	sf::Vector2f getVelocity() const;
	void setVelocity(const sf::Vector2f v);
	bool CheckGroundCollision();
	sf::FloatRect getInnerBoundsForCollision();
	sf::FloatRect getGlobalBoundsForCollision();
	//sf::Sprite getSpriteOfWeapon();
	//void drawBullets(sf::RenderWindow& m_window);
	void setAnimationByDirection(Direction dir);
	Direction getDir();
	void innerUpdater();
	sf::RectangleShape getCurrInnerBoundToDrawOnly() const;
	void setHp();
	void LostHp(int GunDamage);
	int GetHp();
	void LostLife();
	int GetLives();
	void setLivers();
	void setAfterCollisionTimer();
	sf::Time CheckAfterCollisionTimer();
	void minusTimer(sf::Time delta);
	void SaveHp(int hp);

	void SaveLives(int live);

private:
	sf::Time m_timer = sf::Time();
	int coun = -1;
	int m_lives = 6;
	int m_points = 0;
	//ShotgunWeap m_shotgun;
	//DefaultWeap m_defaultWep;
	//RifleWeap m_rifleWep;
	////FireWeap m_fireWep;
	bool arr[WEAPON_NUM] = { true,false,false/*,false*/ },
		isJumping = false,
		m_isGoingDown = false;
	//sf::FloatRect m_InnerBounds;
	float m_jumpHieght = 200.0f;
	sf::Texture m_texture = sf::Texture(), m_dieTexture=sf::Texture();
	sf::Sprite m_sprite;
	bool m_died = false;
	int m_hp = 5;
	Resources::Objects m_bOrb /*= Resources::BLIP*/;
	Resources::Objects m_WeapT/* = Resources::STANDARDBULLET*/;
	Animations m_animation;
	Direction m_dir = Direction::Stay;
	Direction m_LastDir = Direction::Stay;
	Direction m_headingLeftOrRight = Direction::Right;
	float movementSpeed = 400.f;
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	/*std::map<std::tuple<Resources, Resources, Direction>, sf::FloatRect>*/;
	std::pair<sf::FloatRect, sf::FloatRect> m_InnerBoundsRectArr[Resources::Objects::Max][Resources::Objects::Max][MAXDIRECTIONS] ;
	/*float m_currGravity = 0;
	float m_currJumpForce = 0;*/
	float m_dx = 0, m_dy = 0;
	//DefaultWeap* m_defWeap = new DefaultWeap();
	//std::vector <DefaultWeap*> m_defWeapp;
	sf::Color normalColor = m_sprite.getColor();
	sf::Color transparentColor = sf::Color(normalColor.r, normalColor.g, normalColor.b, 128);
	bool isCharacterVisible = true;

};
#endif