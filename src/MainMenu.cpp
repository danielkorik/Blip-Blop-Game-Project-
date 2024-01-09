#include"MainMenu.h"

//====================================
//~constructor
MainMenu::MainMenu(sf::RenderWindow& window)
	:m_window(window), m_isRunning(true) {
	//open font
	if (!m_font.loadFromFile("rogers.ttf"))
	{
		std::cout << "couldn't load font\n";
		exit(EXIT_FAILURE);

	}
	//open blip pic to the menu
	if (!m_blip.loadFromFile("Blip.jpg")) {
		std::cout << "couldn't load Blip\n";
		exit(EXIT_FAILURE);
	}
	//open blop pic to the menu
	if (!m_blop.loadFromFile("Blop.jpg")) {
		std::cout << "couldn't load Blop\n";
		exit(EXIT_FAILURE);
	}
};
//==============================================
//set the menu
void MainMenu::setMenu()
{
	int option = 0;

	sf::Text tex = sf::Text();
	while (option < 3){
		
		tex.setCharacterSize(40);
		tex.setFillColor(sf::Color::White);
		tex.setFont(m_font);
		tex.setPosition(sf::Vector2f((WINDOW_WIDTH / 2) - 100, (WINDOW_HEIGHT / 3) + (option - MENU_ITEMS_NUMBER / 2) * 50));

		m_options.push_back(tex);
		option++;
	}

	m_options[0].setString("Start Game");
	m_options[1].setString("Help");
	m_options[2].setString("Exit");

	static auto background = sf::Texture();

	if (!background.loadFromFile("menuBackground.png"))
	{
		std::cout << "Loading background failed";
		exit(EXIT_FAILURE);
	}
	
	m_background.setTexture(background);
	m_background.setScale(WINDOW_WIDTH / m_background.getGlobalBounds().width, WINDOW_HEIGHT / m_background.getGlobalBounds().height);	
	m_background.setPosition(0, 0);
}
//========================================
//chech if the menu is running
bool MainMenu::isMenuRunning() const
{
	return m_isRunning;
}
//====================================================
//change the menu conditions
void MainMenu::changeMenuRunning()
{
	if (m_isRunning)
		m_isRunning = false;
	else
		m_isRunning = true;
}
//==============================================================
//drawing the charactes textures and saves for us the character that have been selected
void MainMenu::CharachterSelect(int& Char)
{
	m_window.clear();
	m_b1.setTexture(m_blip);	
	m_b1.setPosition(0, 0);
	m_b1.setScale(WINDOW_WIDTH / m_b1.getGlobalBounds().width, (WINDOW_HEIGHT /2)/ m_b1.getGlobalBounds().height);

	m_b2.setTexture(m_blop);
	m_b2.setPosition(0, WINDOW_HEIGHT / 2);
	m_b2.setScale(WINDOW_WIDTH / m_b2.getGlobalBounds().width, (WINDOW_HEIGHT / 2) / m_b2.getGlobalBounds().height);

	while (m_window.isOpen())
	{
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
					sf::Vector2f mousePosF = m_window.mapPixelToCoords(mousePos);

					if (m_b1.getGlobalBounds().contains(mousePosF)) {

						//CHARACTER_SELECTED = _BLIP;
						std::cout << "blip\n";
						Char = _BLIP;
						break;
					}
					else if (m_b2.getGlobalBounds().contains(mousePosF))
					{
						std::cout << "blop\n";

						//CHARACTER_SELECTED = _BLOP;
						Char = _BLOP;
						break;
					}
				}
			}
			break;	
		}
		if (Char != -1)
			break;

		m_window.clear();
		m_window.draw(m_b1);
		m_window.draw(m_b2);
		m_window.display();
	}
}
//================================================================
//function that draws the help string and window
void MainMenu::openHelpOption() const
{
	static sf::Text m_help = sf::Text();
	static sf::Text m_back = sf::Text();


	m_help.setFont(m_font);
	m_help.setCharacterSize(24);
	m_help.setFillColor(sf::Color::White);
	m_help.setString("BlipAndBlop Game Help\n\n"
               "Survive And Live The Adventure!\n"
               "defeat enemies, and reach the end of each map ,\n"
			   "Don't Forget That The Boss In End Of Each Map,\n"
			   "Is The Real Challenge!!.\n\n"
               "Controls:\n"
               "UpArrow - Move Up\n"
               "DownArrow - Move Down\n"
               "LeftArrow - Move Left\n"
               "RightArrow - Move Right\n"
               "Space - Jump\n"
               "P - Perform Attack\n\n"
               "strategy And Speed are key!\n"
               "Avoid enemy attacks, collect power-ups, \n"
			   "Unleash your special attack to Kill Your Enemy Faster.\n\n"
			   "Good luck and enjoy the adventures of BlipAndBlop Game!");
	m_help.setPosition(sf::Vector2f((WINDOW_WIDTH / 2) - 400, 200));
	m_back.setFont(m_font);
	m_back.setFillColor(sf::Color::White);
	m_back.setString("<<Back");
	m_back.setPosition(sf::Vector2f(50, 50));

	bool isback = false;

	while (m_window.isOpen())
	{
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
			if (sf::Event::MouseMoved) //if there is a movement in the mouse from the user gets the coordinates
				///and checks if the user is on an option
			{
				auto location = m_window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				if (m_back.getGlobalBounds().contains(location))
					m_back.setFillColor(sf::Color::Red);
				else
					m_back.setFillColor(sf::Color::White);
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
					sf::Vector2f mousePosF = m_window.mapPixelToCoords(mousePos);

					if (m_back.getGlobalBounds().contains(mousePosF)) {

						isback = true;
					}
				}
			}
			break;
		}
		if (isback == true)
			break;

		m_window.clear();
		m_window.draw(m_back);
		m_window.draw(m_help);
		m_window.display();
	}
}
//===========================================================
std::vector<sf::Text> MainMenu::getMenuOptions() const
{
	return m_options;
}
//=====================================
void MainMenu::ifMouseOn(sf::Vector2f location)
{
	for (int i = 0; i < m_options.size(); i++)
	{
		if (m_options[i].getGlobalBounds().contains(location))
			m_options[i].setFillColor(sf::Color::Red);
		else
			m_options[i].setFillColor(sf::Color::White);
	}
}
//=========================================
//clear the vectors
void MainMenu::clearVec()
{
	m_buttons.clear();
	m_options.clear();
	
}
//==========================================
//Draw the menu
void MainMenu::drawMenu() const
{
	m_window.clear();
	m_window.draw(m_background);
	for (auto i:m_options)
	{
		m_window.draw(i);
	}
}