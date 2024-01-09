#include"Platform.h"

//=========================================
//~c-tor
Platform::Platform()
{
}
//=========================================
//~c-tor
Platform::Platform(const std::vector<sf::Vector2f> v)
{
	m_platform.setFillColor(sf::Color::Red);
	setPlatformPoints(v);
}
//=========================================
//set the platform points 
void Platform::setPlatformPoints(const std::vector<sf::Vector2f> v)
{
	m_platform.setPointCount(v.size());
	for (int i = 0; i < v.size();i++) 
		m_platform.setPoint(i, v[i]);
}
//=========================================
//Get the platform
sf::ConvexShape Platform::getPlatform() const
{
	return m_platform;
}
