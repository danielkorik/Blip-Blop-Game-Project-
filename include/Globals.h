#ifndef _GLOB
#define _GLOB


//=========================================
//enum Guntype 
enum GUNTPE {
	_DEFG,
	_SHOTG,
	_RIFLEG,
	_MAXG
};

//=========================================
//menu choices

enum MENUCHOICES {

	_STARTGAME,
	_HELP,
	_EXIT,
	_MAXCHOICES
};
//=========================================
//user characters
enum USERCHARACTERS {
	_BLIP,
	_BLOP,
	_MAXCHARACTERS
};
//=========================================
//consts that used in game
const int MENU_ITEMS_NUMBER = 3;
const int WEAPON_NUM = 3;
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const int GroundLimit = 950;
const float Gravity = 8.8f;
const float jumpForce = 9;
const int NUMOFPLATFORMSSTAGE1 = 51;
const float MAPSCALE = 1.87f;
const int MAXDIRECTIONS = 11;
const int SHOTGUNAMMOCAPACITY = 20;
const int RIFLEGUNAMMOCAPACITY = 50;



#define SHOTGUN_SHOT "shotGunSound.ogg"
#define RIFLE_SHOT "RifleSound.ogg"
#define DEFAULT_SHOT "DeafultWeaponSound.ogg"
#define SHOTGUN_WORD_VOICE "shotGunWord.opus"
#define RIFLE_WORD_VOICE "machineGunWord.opus"




#endif