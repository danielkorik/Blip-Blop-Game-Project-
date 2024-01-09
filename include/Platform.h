#ifndef _PLATFORM
#define _PLATFORM

#include<SFML/Graphics.hpp>

// ~Platform class
class Platform {
public:
	Platform();	//c-tor
	Platform(const std::vector<sf::Vector2f> v);
	void setPlatformPoints(const std::vector<sf::Vector2f> v);//getting a vector of points
	sf::ConvexShape getPlatform() const;
private:
	sf::ConvexShape m_platform;
};

#endif