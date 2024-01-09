#ifndef _ANIMATION
#define _ANIMATION


#include<SFML/Graphics.hpp>
#include"Direction.h"
#include"AnimationData.h"
#include "Resources.h"

class Animations {

public:
	Animations(AnimationData& data, Direction dir, sf::Sprite& sprite,int png);
	void direction(Direction dir);
	void update(sf::Time delta);
	sf::Sprite GetAnimationSprite();
	Direction Getdirection();

	void update();
private:
	AnimationData& m_data;
	sf::Time m_elapsed = {};
	Direction m_dir = Direction::Stay;
	int m_index = 0;
	sf::Sprite& m_sprite;



};
#endif