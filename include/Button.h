#ifndef _BUTTON
#define _BUTTON
#include<SFML/Graphics.hpp>

class Button {
	Button() {};
	sf::Texture m_textures;
	sf::RectangleShape m_shape;
};

#endif