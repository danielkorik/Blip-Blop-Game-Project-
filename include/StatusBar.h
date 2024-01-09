#ifndef _STATUSBAR
#define _STATUSBAR


#include "Globals.h"
#include<SFML/Graphics.hpp>
#include"Characters.h"
#include"BlipAndBlop.h"

// ~StatusBar class 
class StatusBar {

public:
StatusBar();
void DrawStatusBar(sf::RenderWindow& window,int hp);
void setPostion(sf::Vector2f pos);
void setText(int lives, sf::Vector2f pos);
sf::Sprite getSprite(int index);
void setScore(int score, sf::Vector2f pos);
sf::Font GetFont();
void setWinText(int score, sf::Vector2f pos);
void DrawWinText(sf::RenderWindow& window);
void GarGamelSetText(sf::Vector2f pos);
void DrawGarGamelText(sf::RenderWindow& window);
void setLoseText(int score, sf::Vector2f pos);
void DrawLoseText(sf::RenderWindow& window);

private:
sf::Texture m_texture[6];
sf::Sprite m_sprite[6];
int m_gunType =  _DEFG;
int m_specialAtk = 0;
sf::Text m_text,m_scoreText,m_winText,m_GarGamelText,m_LoseText;
sf::Font m_font;
};
#endif //_STATUSBAR
