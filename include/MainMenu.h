#ifndef _MAINMENU
#define _MAINMENU

#include"Button.h"
#include"Globals.h"
#include<iostream>

// ~MainMenu class
class MainMenu {

public:
	MainMenu(sf::RenderWindow& window); //c-tor
	void drawMenu()const;
	void setMenu();
	bool isMenuRunning()const;
	void changeMenuRunning();
	void CharachterSelect(int& Char);
	void openHelpOption()const;
	std::vector <sf::Text> getMenuOptions() const;
	void ifMouseOn(sf::Vector2f location);
	void clearVec();

private:
	sf::Font m_font;
	sf::RenderWindow& m_window;
	std::vector<std::unique_ptr<Button>> m_buttons;
	sf::Texture m_text = sf::Texture();
	bool m_isRunning ;
	std::vector <sf::Text> m_options;
	sf::Sprite m_background , m_b1,m_b2;
	sf::Texture m_blip = sf::Texture();
	sf::Texture m_blop = sf::Texture();
};

#endif