#ifndef _GAME
#define _GAME


#include<iostream>
#include<SFML/Graphics.hpp>
#include"Board.h"
#include"Characters.h"
#include"MainMenu.h"
#include"BlipAndBlop.h"
#include"StatusBar.h"
#include"Resources.h"
#include<iostream>
#include "StandardEnemy.h"
#include"DefaultWeap.h"
#include"ShotgunWeap.h"
#include"RifleWeap.h"
#include "ForkEnemy.h"
#include <chrono>
#include"Boss.h"
#include"BossBullet.h"
#include <thread>
#include "PresentEnemy.h"

//~class Game
class Game {

public:
	Game();
	~Game(){};
	void run();
	void update();
	void checkBottunPressed(const sf::Vector2f mousePosF);
	void play();
	void drawPlatforms();
	void updateAndCheckIfBulletsInTheField(const sf::FloatRect& view);
	void CheckForLockScreens();
	void draw();
	void checkCollision();
	void BulletsFiring();
	void createEnemies();
	void createStandardEnemiesPos();
	void createForkEnemiesPos();
	void createPresentEnemiesPos();
	void clearVectors();
	void drawAndCreateEnemies();
	void createStandardEnemy();
	void createPresentEnemy();
	void createForkEnemy();
	void createBossPos();
	void createBossEnemy();

private:
	sf::Music& MenuMusic = Resources::instance().getMenuMusic();//music
	sf::Music& GameMusic = Resources::instance().getGameMusic();//music

	sf::Sound m_sound;
	sf::RenderWindow  m_window;
	BlipAndBlop* m_p1 =  new BlipAndBlop(Resources::BLIP, Resources::STANDARDBULLET);
	StandardEnemy* m_se1 = new StandardEnemy();
	sf::Time m_BulletsTimer = sf::seconds(0.3);
	sf::View view;
	sf::Sprite mapSprite;
	sf::Clock clock;
	sf::Clock clock2;
	sf::Clock clock3;
	std::vector<sf::Vector2f> m_lockSreensPos = { {535 * MAPSCALE,WINDOW_HEIGHT / 2},
		{1565 * MAPSCALE,WINDOW_HEIGHT / 2},
		{4000 * MAPSCALE,WINDOW_HEIGHT / 2},
		{7546*MAPSCALE,WINDOW_HEIGHT/2},
		{9475*MAPSCALE,WINDOW_HEIGHT/2},
		{11781*MAPSCALE,WINDOW_HEIGHT/2},
		{13487*MAPSCALE,WINDOW_HEIGHT/2},
		{14221 * MAPSCALE,WINDOW_HEIGHT / 2} };
	bool LockScreenLeft = false,
		LockScreenRight = false,
		LockScreen = false;
	int m_score = 0;
	int BOSSSIZE = 4;
	bool m_TextIsOn = false;
	sf::Time m_deltaTime = {}, m_deltaTime2 = {}, m_timer = {}, m_TextOnScreenTimer = sf::seconds(5);
	MainMenu m_menu = MainMenu(m_window);
	StatusBar m_status;
	Board m_board;
	bool m_startGame = false;
	//MainMenu m_menu;
	int CHARACTER_SELECTED = -1;
	Resources m_resource;
	std::vector <DefaultWeap*> m_defWeapp;
	std::vector <ShotgunWeap*> m_ShotWeap;
	std::vector <RifleWeap*> m_RifleWeap;
	std::vector <StandardEnemy*> m_standardEnemies;
	std::vector <PresentEnemy*> m_presentEnemies;
	std::vector <ForkEnemy*> m_forkEnemies;
	std::vector <Boss*> m_BossEnemies;
	std::vector<BossBullet*> m_BossBull;

	std::vector<sf::Vector2f> m_sEnemPos;
	std::vector<sf::Vector2f> m_pEnemPos;
	std::vector<sf::Vector2f> m_fEnemPos;
	std::vector<sf::Vector2f> m_BossPos;

	//sf::Text m_textWin;
	sf::Text m_textLost;
	bool m_WinGame = false;

	Direction m_direction;
	bool m_isFiring = false;
	std::vector<Platform> platformsToCheckCollision;
	sf::FloatRect m_lastPositionOfBlip;
	ShotgunWeap m_shotgunWeap;
	RifleWeap m_RifleGunWeap;
	bool m_ShotGun = false, m_rifle = false;


	const float lockScreenOffset = 200.0f; // Adjust this value as needed


};

#endif