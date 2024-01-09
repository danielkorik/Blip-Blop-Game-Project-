#include"StatusBar.h"

//==========================================
//~c-tor
StatusBar::StatusBar()
{

	sf::IntRect rec[6];

	rec[0] = sf::IntRect(sf::Vector2i(317, 817), sf::Vector2i(60, 60));
	rec[1] = sf::IntRect(sf::Vector2i(258, 817), sf::Vector2i(57, 60));
	rec[2] = sf::IntRect(sf::Vector2i(193, 816), sf::Vector2i(60, 60));
	rec[3] = sf::IntRect(sf::Vector2i(131, 817), sf::Vector2i(60, 60));
	rec[4] = sf::IntRect(sf::Vector2i(68, 817), sf::Vector2i(60, 60));
	rec[5] = sf::IntRect(sf::Vector2i(5, 816), sf::Vector2i(60, 60));

	for (int i = 0; i < 6; i++)
	{
		if (!m_texture[i].loadFromFile("characterSprite.png",rec[i]))
		{
			throw std::runtime_error("Can't load Status Texture\n");

		}
		m_sprite[i].setTexture(m_texture[i]);
		m_sprite[i].setPosition(10 * MAPSCALE, 10 * MAPSCALE);
		m_sprite[i].setScale(1.87, 1.87);
	}
	if (!m_font.loadFromFile("rogers.ttf"))
	{
		std::cout << "couldn't load font\n";
		exit(EXIT_FAILURE);

	}
	m_text.setString("3");
	m_text.setFillColor(sf::Color::Red); // Set the fill color of the text
	m_text.setScale(MAPSCALE, MAPSCALE);
	m_text.setFont(m_font);


	m_scoreText.setString("0");
	m_scoreText.setFillColor(sf::Color::White); // Set the fill color of the text
	m_scoreText.setScale(MAPSCALE, MAPSCALE);
	m_scoreText.setFont(m_font);



	m_winText.setFont(m_font);
	m_winText.setScale(MAPSCALE, MAPSCALE);
	m_winText.setFillColor(sf::Color::Cyan);


	m_GarGamelText.setFont(m_font);
	m_GarGamelText.setScale(MAPSCALE, MAPSCALE);
	m_GarGamelText.setFillColor(sf::Color::Black);

	m_LoseText.setFont(m_font);
	m_LoseText.setScale(MAPSCALE, MAPSCALE);
	m_LoseText.setFillColor(sf::Color::Red);

}
//==========================================
//draw function of the statusbar
void StatusBar::DrawStatusBar(sf::RenderWindow& window, int hp)
{
	window.draw(m_sprite[hp]);
	window.draw(m_text);
	window.draw(m_scoreText);


}
//==========================================
//set the postion 
void StatusBar::setPostion(sf::Vector2f pos)
{
	for (int i = 0; i < 6; i++)
	{
		m_sprite[i].setPosition(pos);
	}
}
//==========================================
//set the text of the status bar
void StatusBar::setText(int lives, sf::Vector2f pos)
{
	m_text.setPosition(pos);

	m_text.setString(std::to_string(lives));
}
//==========================================
//set the score text 
void StatusBar::setScore(int score, sf::Vector2f pos)
{
	m_scoreText.setPosition(pos);

	m_scoreText.setString(std::to_string(score));
}
//==========================================
//getting the font
sf::Font StatusBar::GetFont()
{
	return m_font;
}
//==========================================
//set the win text
void StatusBar::setWinText(int score,sf::Vector2f pos)
{
	m_winText.setString("CONGRATULATIONS!!!\nYOU WON THE GAME!!\n\n YOUR SCORE IS: " + std::to_string(score));

	m_winText.setPosition(pos);

}
//==========================================
//set the lost text 
void StatusBar::setLoseText(int score, sf::Vector2f pos)
{
	m_LoseText.setString("OH NO! YOU LOST :(\n~~GAMEOVER~~\n\n YOUR SCORE IS: " + std::to_string(score) + "\nBETTER LUCK NEXT\nTIME!");

	m_LoseText.setPosition(pos);

}
//==========================================
//draw the win text 
void StatusBar::DrawWinText(sf::RenderWindow& window)
{
	window.draw(m_winText);
	window.display();
}
//==========================================
//draw the lost text
void StatusBar::DrawLoseText(sf::RenderWindow& window)
{
	window.draw(m_LoseText);
	window.display();
}
//==========================================
//set the gargamel text
void StatusBar::GarGamelSetText(sf::Vector2f pos)
{
	m_GarGamelText.setString("B.L.P: OH NO!\nTHE POOR OLD MAN\nHAS BEEN KILLED!\nTHOSE RESPONSIBLE FOR\nTHIS INFAMY WILL PAY,\n I SWEAR!");
	m_GarGamelText.setCharacterSize(20);
	m_GarGamelText.setPosition(pos);

}
//==========================================
//draw the gargamel text
void StatusBar::DrawGarGamelText(sf::RenderWindow& window)
{
	window.draw(m_GarGamelText);
}
//==========================================
sf::Sprite StatusBar::getSprite(int index)
{
	return m_sprite[index];
}