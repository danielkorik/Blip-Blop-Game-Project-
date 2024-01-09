#ifndef _BOARD
#define _BOARD

#include<SFML/Graphics.hpp>
#include"Platform.h"
#include"Characters.h"
#include "Globals.h"

// ~class Board
class Board{
public:
	Board();	//c-tor
	std::vector<float> splitString(const std::string& line);
	void createPlatforms();
	std::vector<Platform> getPlatformsToDraw() const;
	bool checkCollisionBetweenTwoSprites(sf::Sprite sp1, sf::Sprite sp2);
	void clearVec();


private:
	sf::Texture m_texture = sf::Texture();
	sf::RectangleShape m_shape = sf::RectangleShape();
	std::vector<Platform> m_platforms;
	std::vector<Platform> m_currPlatforms;
	std::vector<std::vector<sf::Vector2f>> m_platformsPoints ;
	int GravityLimit = 700.0f;
};
#endif