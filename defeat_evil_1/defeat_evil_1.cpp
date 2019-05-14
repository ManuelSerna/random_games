// Author: Manuel Serna-Aguilera
// GAME TITLE: Defeat Evil!

// DIRECTORIES ***************************************************
#include "DarkGDK.h"

// GLOBAL VARIABLES **********************************************
// All Level-Related Constants (1-20)
const int SPACE_NUM = 1;// space
const int SPACE_MUSIC = 1;// mute city
const int SPACE_COORDS_NUM = 11;

const int GLAND_NUM = 2;// grassy plain
const int GRASS_MUSIC = 2;// venom
const int GRASS_COORDS_NUM = 12;

const int DLAND_NUM = 3;// desert
const int DESERT_MUSIC = 3;// dire emblem
const int DESERT_COORDS_NUM = 13;

const int OCEAN_NUM = 4;// ocean
const int OCEAN_MUSIC = 4;// big blue
const int OCEAN_COORDS_NUM = 14;

const int ILAND_NUM = 5;// gelid (ice) world
const int GELID_MUSIC = 5;// mach rider
const int GELID_COORDS_NUM = 15;

const int LAVA_NUM = 6;// volcanic expanse
const int VOL_MUSIC = 6;// brinstar
const int VOL_COORDS_NUM = 16;

const int MEGA_NUM = 7;// night megalopolis
const int MEGA_MUSIC = 7;// brinstar depths
const int MEGA_COORDS_NUM = 17;

const int HYPER_NUM = 8;// hyperspace
const int HYPER_MUSIC = 8;// mm melee 2
const int HYPER_COORDS_NUM = 18;

const int ALIEN_W = 9;// alien world
const int ALIEN_MUSIC = 9;// mm melee 1
const int ALIEN_COORDS_NUM = 19;

const int ENEMY_FORT = 10;// last enemy stronghold
const int ENEMY_FORT_MUSIC = 10;// final destination
const int FORT_COORDS_NUM = 20;
//****************************************************************
// Power-Up Constants (30-39)
const int POWR_NUM = 30;// multiple laser power-up
const int HYPR_SHIP_NUM = 31;// super-fast ship power-up
const int HYPR_LSR_NUM = 32;// super-fast laser power-up
//****************************************************************
// Player Ship Constants (40-49)
const int SHIP_NUM = 40;// your ship
const int LASR_NUM = 41;// main laser
	const int LASR_1 = 42;// clone lasers
	const int LASR_2 = 43;
const int HEALTH_NUM = 44;// health units for player ship
const int HEALTH_TITLE_NUM = 45;// displays "HEALTH"
const int BLSR_NUM = 49;// your own big laser
//****************************************************************
// All Enemy Constants (50-69)
const int ENEM_NUM = 50;// enemy sprite 1
const int ENEM_2_NUM = 51;// clone enemy sprites
const int ENEM_3_NUM = 52;

const int ELSR_NUM = 53;// enemy laser
const int ELSR_2_NUM = 54;// cloned lasers
const int ELSR_3_NUM = 55;

const int LVL_BOSS_NUM = 56;// level boss
const int LB_LSR_NUM = 57;// boss laser (rather big)
const int BOSS_HEALTH_NUM = 58;// boss health bar
const int BOSS_HEALTH_TITLE = 59;// boss health bar title

const int EMPEROR_NUM = 60;// the emperor
const int EMP_SLSR_NUM = 61;// emperor's laser (small)
const int EMP_LSR_NUM = 62;// emperor's laser (big)
const int EMP_HEALTH_BAR_NUM = 63;// emperor's health bar
const int EMP_HEALTH_BT_NUM = 64;// emperor's health bar title
//****************************************************************
// Other Screen Constants (90-99)
const int LOAD_NUM = 90;// loading screen
const int INTRO_NUM = 91;// intro screen
const int CONTROL_NUM = 92;// controls screen
const int STORY_NUM = 93;// exigence/story screen
const int FAIL_NUM = 94;// failure screen
const int SUCC_NUM = 95;// success screen
//****************************************************************
// Sound Effects Constants (100-109)
const int SHIP_LSR = 100;// ship
const int ENEM_LSR = 101;// reg enemy
const int LBOS_LSR = 102;// boss
const int EMPR_LSR = 103;// emperor
//****************************************************************
// Music Constants (100+)
const int INTRO_MUSIC = 100;// How to Play (for title, controls, and story screens)
const int BOSS_MUSIC = 101;// level boss music, metal battle
const int EMPEROR_MUSIC = 102;// emperor music, 
const int FAIL_MUSIC = 103;// challenger! (plays only once)
const int SUCC_MUSIC = 104;// poke floats
//****************************************************************
// FUNCTION PROTOTYPES********************************************
void setup();// turns on manual refresh, color key, and randomizer
void loadFiles();// load all the files you can (in case of hardware problems)
void introduction();// all screens displayed before main game
	void renderLevel(int, int &, int &, int, int &);// loops background and generates random number
		void setLevel(int &, int &, bool &);// will receive "currentLevel" and will subsequently determine level
	void playerShip(int &, int &, int &, int, int, int, int, int &, int &, int &, bool &, int &, int &,
		int &, int &, int, int, int);// all player ship mechanics here (18 tot var)
	void powerups(int, bool &, int &, int &, int, int, bool &, int &, int &, bool &, int &, bool &, int &, int &,
		bool &, int &, int &, bool &, int &, int &, bool &, int &, int &);// mechanics for power-ups (23 var total)
	void regularEnemy(int, int, int, int, int, int, int &, int &, int &, int &, int &, bool &, bool &, int &, int &, 
		bool &, bool &, int &, int &, int, int);// all regular enemy mechanics, used for all three enemies (21 var total)
	void levelBoss(int, int, int, int, int, int, int, int, int, int, int &, int &, int &, int &, int &, int &, 
		int &, int &, int &, int &, int &, int &, int &, int &, bool &, bool &, bool &, bool &, bool &, bool &, 
		bool &, bool &, bool &, bool &, bool &, bool &, bool &, bool &);// all level boss mechanics (38 var total)
	void theEmperor(int, int, int, int, int, int, int, int, int, int, int, int, int, int, int &, int &, int &, int &, 
		int &, int &, int &, int &, int &, int &, int &, bool &, bool &, bool &, bool &, bool &, bool &, bool &, 
		bool &, bool &, bool &, bool &, bool &, bool &, bool &, bool &);// all emperor mechanics (40 var total)

//****************************************************************
// THE MAIN GAME FUNCTION ****************************************
void DarkGDK()
{
	// PUT TITLE IN WINDOW ************************************************************************
	dbSetWindowTitle("Defeat Evil!");

	// ESSENTIAL VARIABLES ************************************************************************
	int result;// used to determine: power-ups, enemy actions, etc
	int currentLevel = 1;// used to determine level background (increments), always starts at one
	int requiredStrikes = 24;// resets deathToll after each level
	int deathToll = 24;// enemy kills needed for level boss to appear, decremented (24-26 recommended)
	bool scanLevel = true;// allows compiler to go through setLevel function once before every level
	int backSpeed;// speed background moves, different for each one
	int backX = 0;// used to move background

	const int WIDTH = dbScreenWidth();// screen width
	const int HEIGHT = dbScreenHeight();// screen height

	// GAME SETUP *********************************************************************************
	setup();// turns on manual refresh and color key
	loadFiles();// set up various things like loading images, sound, & music

	// SHIP VARIABLES *****************************************************************************
	int shipX = WIDTH * 1/4;// starting x & y coords
	int shipY = HEIGHT/2;
	int shipSpeed = 6;// speed of ship when directional keys are pressed (6 is default)
		// Center the insertion point for ship
		dbSprite(SHIP_NUM, shipX, shipY, SHIP_NUM);
		// Simplify ship sprite width and height variables
		int shipW = dbSpriteWidth(SHIP_NUM);
		int shipH = dbSpriteHeight(SHIP_NUM);
		// Offset ship with new variables and hide sprite
		dbOffsetSprite(SHIP_NUM, shipW/2, shipH/2);
		dbHideSprite(SHIP_NUM);
	// Ship laser
	bool laserBlast = false;// will be checked if "trigger" has been pressed
	int laserSpeed = 27;// speed of laser blast (27 is the default speed)
	int laserX = shipX;// both laser coords will be updated
	int laserY = shipY;
	// Ship health
	int health = 35;// 35 units is the initial HP
	int hit = 10;// value by which health bar decrements (sprite "stretched")
	// hit times health must equal healthW in order for the bar and health to deplete at the same rate
	int healthW = 350;// width for health bar, to be modified
	int hBarX = WIDTH * 1/4;
	int hBarY = 10;
	int hTitleX = WIDTH * 1/4 - 110;// health bar coords
	int hTitleY = 10;

	// POWER UP VARIABLES *************************************************************************
	// Multi-laser variables
	bool multiIcon = false;// for power-up icon to appear
	bool multiLaser = false;// activates this power-up
	int mulX = dbRND(WIDTH * 3/4);// randomize drop x range (to the middle from the left)
	int mulY = -100;
	int laserFuel = 350;// fuel left for multi-laser ability
	// Hyper ship variables
	bool shipIcon = false;// for power-up icon to appear
	bool shipHyper = false;// activates this power-up
	int hyperShipX = dbRND(WIDTH * 3/4);// randomize drop x-range
	int hyperShipY = -100;
	int boost = 400;// boost left for hyper ship power-up
	// Hyper laser variables
	bool laserIcon = false;// for power-up icon to appear
	bool laserHyper = false;// activates this power-up
	int hyperLaserX = dbRND(WIDTH * 3/4);// randomize drop x-range
	int hyperLaserY = -100;
	int laserBoost = 250;// boost left for hyper lasers

	// REGULAR ENEMY VARIABLES ********************************************************************
	// Enemy One ----------------------------------------------------------------------------------
	int enemyOne = ENEM_NUM;// replace constants to apply to function
	int enemyOneLaser = ELSR_NUM;

	bool enemy1Appear = true;// enemy will appear if death toll hasn't been reached
	int enemy1X = WIDTH + 150;// enemy sprite coords (for original enemy)
	int enemy1Y = dbRND(HEIGHT);// new set of y coords every time reg enemy spawns
		// Laser components
		bool enemy1Shoot = true;// controls when enemy will shoot (off when boss appears)
		bool enemy1Laser = false;// will be true if result is a certain number
		int enemy1LaserX = enemy1X;// enemy laser coords (updated)
		int enemy1LaserY = enemy1Y;
	// Enemy Two ----------------------------------------------------------------------------------
	int enemyTwo = ENEM_2_NUM;// replace constants to apply to function
	int enemyTwoLaser = ELSR_2_NUM;

	bool enemy2Appear = true;// enemy will appear if death toll hasn't been reached
	int enemy2X = WIDTH + 150;// enemy sprite coords (for original enemy)
	int enemy2Y = dbRND(HEIGHT);// new set of y coords every time reg enemy spawns
		// Laser components
		bool enemy2Shoot = true;// controls when enemy will shoot (off when boss appears)
		bool enemy2Laser = false;// will be true if result is a certain number
		int enemy2LaserX = enemy2X;// enemy laser coords (updated)
		int enemy2LaserY = enemy2Y;
	// Enemy Three --------------------------------------------------------------------------------
	int enemyThree = ENEM_3_NUM;// replace constants to apply to function
	int enemyThreeLaser = ELSR_3_NUM;

	bool enemy3Appear = true;// enemy will appear if death toll hasn't been reached
	int enemy3X = WIDTH + 150;// enemy sprite coords (for original enemy)
	int enemy3Y = dbRND(HEIGHT);// new set of y coords every time reg enemy spawns
		// Laser components
		bool enemy3Shoot = true;// controls when enemy will shoot (off when boss appears)
		bool enemy3Laser = false;// will be true if result is a certain number
		int enemy3LaserX = enemy3X;// enemy laser coords (updated)
		int enemy3LaserY = enemy3Y;
	// General ------------------------------------------------------------------------------------
	int enemySpeed = 1;// speed of (all) enemy craft
	int enemyLaserSpeed = 20;// speed of enemy laser

	// LEVEL BOSS VARIABLES ***********************************************************************
	bool bossAppear = false;// true when death toll for regular enemies reaches zero
	int bossX = WIDTH;// boss coords
	int bossY = HEIGHT/2;
	int bossSpeed = 10;// boss' vertical speed
	bool bossMoveUp = true;// boss moves up or down

	bool bossLaser = false;// determines whether boss shoots or not
	int bossLaserX = bossX;// boss laser coords
	int bossLaserY = bossY;
	int bossLaserSpeed = 40;// laser speed for level boss

	int bossHealth = 100;// boss health
	int bossHit = 5;// decrements bossHealthW
	int bossHealthW = 500;// width of boss health bar

	int bBarX = WIDTH/2 - 250;// boss' health bar coords
	int bBarY = HEIGHT - 50;
	int bTitleX = WIDTH/2 - 43;// boss title centered this way
	int bTitleY = HEIGHT - 60;// y coord 10 pixels up form bar

	// THE EMPEROR VARIABLES **********************************************************************
	bool emperorAppear = false;// dictates whether emperor appears in-game

	int emperorX = WIDTH * 2;// starting x coord
	int emperorY = HEIGHT/2;// sprite centered later

	int emperorSpeed = 2;// emperor's speed, will change (2 to 3)
	bool emperorMoveH = true;// emperor starts by moving forward a bit
	bool emperorMoveV = false;// then emperor moves up and down
	bool emperorMoveUp = true;// determines if emperor moves up or down

	// Big laser components
	bool emperorBigLaser = false;// determines whether emperor will shoot or not
	int emperorBigLaserX = emperorX;// emperor laser coords
	int emperorBigLaserY = emperorY;
	int emperorBigLaserSpeed = 32;// speed of emperor's big laser

	// Small laser components
	bool emperorSmallLaser = false;
	int emperorSmallLaserX = emperorX;
	int emperorSmallLaserY = emperorY;
	int emperorSmallLaserSpeed = 37;

	int emperorHealth = 120;// emperor's health points
	int emperorHit = 5;// decrements emperorHealthW
	int emperorHealthW = 600;// width of emperor's health bar

	int eBarX = WIDTH/2;// emperor's health bar coords
	int eBarY = HEIGHT - 20;//HEIGHT - 25;
	int eTitleX = WIDTH/2;// emperor's health bar title coords
	int eTitleY = HEIGHT - 50;

	// BEGIN GAME ON THE SCREEN *******************************************************************
	introduction();// shows intro screen and exigence on game

	// ENTER GAME LOOP ****************************************************************************
	while( LoopGDK() )
	{
		// Set up for the current level
		if( scanLevel )
		{
			setLevel(currentLevel, backSpeed, scanLevel);
		}

		// Otherwise, switch to game mechanics and gameplay
		else
		{
			// RENDER LEVEL ===========================================================================
			renderLevel(currentLevel, backX, backSpeed, WIDTH, result);

			// THE PLAYER SHIP ========================================================================
			playerShip(shipX,  shipY,  shipSpeed, shipW, shipH, hTitleX, hTitleY, hBarX, hBarY, healthW, 
				laserBlast, laserX, laserY, laserSpeed, health, currentLevel, WIDTH, HEIGHT);

			// ALL POWER-UPS ==========================================================================
			powerups(result, multiIcon, mulX, mulY, WIDTH, HEIGHT, multiLaser, laserX, laserY, laserBlast, 
				laserFuel, shipIcon, hyperShipX, hyperShipY, shipHyper, shipSpeed, boost, laserIcon,
				hyperLaserX, hyperLaserY, laserHyper, laserSpeed, laserBoost);

			// REGULAR ENEMIES (3) ====================================================================
			// Enemy One
			regularEnemy(WIDTH, HEIGHT, result,  hit, enemySpeed, enemyLaserSpeed, shipX, shipY, health, 
				healthW, deathToll, laserBlast, enemy1Appear, enemy1X, enemy1Y, enemy1Shoot, enemy1Laser, 
				enemy1LaserX, enemy1LaserY, enemyOne, enemyOneLaser);
			// Enemy Two
			regularEnemy(WIDTH, HEIGHT, result,  hit, enemySpeed, enemyLaserSpeed, shipX, shipY, health, 
				healthW, deathToll, laserBlast, enemy2Appear, enemy2X, enemy2Y, enemy2Shoot, enemy2Laser, 
				enemy2LaserX, enemy2LaserY, enemyTwo, enemyTwoLaser);
			// Enemy Three
			regularEnemy(WIDTH, HEIGHT, result,  hit, enemySpeed, enemyLaserSpeed, shipX, shipY, health, 
				healthW, deathToll, laserBlast, enemy3Appear, enemy3X, enemy3Y, enemy3Shoot, enemy3Laser, 
				enemy3LaserX, enemy3LaserY, enemyThree, enemyThreeLaser);

			// LEVEL BOSS =============================================================================
			levelBoss( bTitleX, bTitleY, bossSpeed, WIDTH, HEIGHT, result, hit, bossHit, requiredStrikes, bossLaserSpeed, 
				deathToll, bossX, bossY, bBarX, bBarY, bossHealthW, bossLaserX, bossLaserY, currentLevel, health, 
				healthW, shipX, shipY, bossHealth, enemy1Appear, enemy2Appear, enemy3Appear, bossAppear, bossLaser, 
				laserBlast, multiIcon, multiLaser, shipIcon, shipHyper, laserIcon, laserHyper, scanLevel, bossMoveUp);

			// THE EMPEROR ============================================================================
			theEmperor(currentLevel, deathToll, emperorSpeed, WIDTH, HEIGHT, result, emperorSmallLaserSpeed, 
				emperorBigLaserSpeed, hit, emperorHit, eTitleX, eTitleY, eBarX, eBarY, emperorX, emperorY, backSpeed, 
				emperorHealthW, emperorSmallLaserX, emperorSmallLaserY, emperorBigLaserX, emperorBigLaserY, health, 
				healthW, emperorHealth, enemy1Appear, enemy2Appear, enemy3Appear, emperorAppear, emperorMoveH, 
				emperorMoveV, emperorMoveUp, emperorSmallLaser, emperorBigLaser, multiIcon, multiLaser, shipIcon, 
				shipHyper, laserIcon, laserHyper);

			dbSync();// refresh screen
		}
	}
	//END GAME LOOP *******************************************************************************
	//*********************************************************************************************
}
// FUNCTION DEFINITIONS ******************************************
// Turn on manual sync rate, color key, and randomizer
void setup()
{
	// Manually control the refresh rate to 60 fps
	dbSyncOn();
	dbSyncRate(60);

	// Reseed random number generator here
	dbRandomize(dbTimer());

	// Set green (255) as color key
	dbSetImageColorKey(0, 255, 0);
}
//****************************************************************
// Load all files necessary to start the game
void loadFiles()
{
	// Load all character and character-related images
	// Player Ship
	dbLoadImage("Ship.bmp", SHIP_NUM);// your ship
	dbLoadImage("Laser.bmp", LASR_NUM);// main laser (& clones)
	dbLoadImage("ShipHealthBar.bmp", HEALTH_NUM);// health units for player ship
	dbLoadImage("ShipHealthTitle.bmp", HEALTH_TITLE_NUM);// displays "HEALTH"
	dbLoadImage("BigLaser.bmp", BLSR_NUM);// your own big laser
	// Power-Ups
	dbLoadImage("MultiLaserIcon.bmp", POWR_NUM);// multiple laser power-up
	dbLoadImage("HyperShipIcon.bmp", HYPR_SHIP_NUM);// super-fast ship power-up
	dbLoadImage("HyperLaserIcon.bmp", HYPR_LSR_NUM);// super-fast laser power-up
	// Regular Enemy
	dbLoadImage("Enemy.bmp", ENEM_NUM);// enemy sprite (& clones)
	dbLoadImage("ELaser.bmp", ELSR_NUM);// enemy laser
	// Level Boss
	dbLoadImage("LevelBoss.bmp", LVL_BOSS_NUM);// level boss
	dbLoadImage("BossLaser.bmp", LB_LSR_NUM);// boss' laser
	dbLoadImage("BossHealthBar.bmp", BOSS_HEALTH_NUM);// boss health bar
	dbLoadImage("BossHealthTitle.bmp", BOSS_HEALTH_TITLE);// boss health bar title
	// The Emperor
	dbLoadImage("TheEmperor.bmp", EMPEROR_NUM);// the emperor
	dbLoadImage("EmperorSmallLaser.bmp", EMP_SLSR_NUM);// emperor's small laser
	dbLoadImage("EmperorBigLaser.bmp", EMP_LSR_NUM);// emperor's big laser
	dbLoadImage("EmperorHealthBar.bmp", EMP_HEALTH_BAR_NUM);// emperor's health bar
	dbLoadImage("EmperorHealthTitle.bmp", EMP_HEALTH_BT_NUM);// emperor's health bar title
	//************************************************
	// Load necessary screen images needed before gameplay
	dbLoadImage("LoadingScreen.bmp", LOAD_NUM);// loading screen
	dbLoadImage("StartScreen.bmp", INTRO_NUM);// starting screen
	dbLoadImage("ControlsScreen.bmp", CONTROL_NUM);// controls screen
	dbLoadImage("StoryScreen.bmp", STORY_NUM);// exigence/story screen

	dbLoadImage("Failure.bmp", FAIL_NUM);// failure screen
	dbLoadImage("Success.bmp", SUCC_NUM);// success screen
	//************************************************
	// Load sound files
	//************************************************
	// Load some music files
	dbLoadMusic("11-LVLBOSS-Metal Battle.mp3", BOSS_MUSIC);
}
//****************************************************************
// Introduction to the game, before gameplay
void introduction()
{
	dbSyncOff();// turn on auto refresh (temporarily)

	// Load intro music
	dbLoadMusic("0-How to Play.mp3", INTRO_MUSIC);

	// 1) Display loading screen and wait 4 secs
	dbSprite(LOAD_NUM, 0, 0, LOAD_NUM);
	dbWait(4000);

	// 2) Play intro music and intro screen
	dbLoopMusic(INTRO_MUSIC);
	dbSprite(INTRO_NUM, 0, 0, INTRO_NUM);
	dbDeleteSprite(LOAD_NUM);// then delete loading screen

	dbWaitKey();// press any key and wait 1 sec
	dbWait(1000);// 1 sec delay

	// 3) Display controls screen
	dbSprite(CONTROL_NUM, 0, 0, CONTROL_NUM);
	dbDeleteSprite(INTRO_NUM);// then delete intro screen image and sprite
	dbDeleteImage(INTRO_NUM);

	dbWaitKey();// press any key and wait 1 sec
	dbWait(1000);// 1 sec delay

	// 4) Now explain the story to the player
	dbSprite(STORY_NUM, 0, 0, STORY_NUM);
	dbDeleteSprite(CONTROL_NUM);// then delete controls screen image and sprite
	dbDeleteImage(CONTROL_NUM);

	dbWaitKey();// press any key and wait 1 sec
	dbWait(1000);// 1 sec delay

	dbDeleteSprite(STORY_NUM);// then delete exigence image and sprite and start game
	dbDeleteImage(STORY_NUM);
	dbDeleteMusic(INTRO_MUSIC);

	dbSyncOn();// return to manual refresh and begin the game
}
//****************************************************************
// Function that decides level, track, and background speed
void setLevel(int &currentLevel, int &backSpeed, bool &scanLevel)
{
	dbSyncOff();// turn on auto refresh (temporarily)

	int wait = 600;// duration time for coord screens

	// Enter a switch case statement to determine level, and load files
	switch(currentLevel)
	{
		// Level 1: Space (same setup for all other levels)
	case 1:
		// Load coords image
		dbLoadImage("SpaceCoords.bmp", SPACE_COORDS_NUM);
		dbSprite(SPACE_COORDS_NUM, 0, 0, SPACE_COORDS_NUM);
		dbWait(wait);// wait
		// delete everything coords-related for this level 
		dbDeleteSprite(SPACE_COORDS_NUM);
		dbDeleteImage(SPACE_COORDS_NUM);

		//Load level image and loop music
		dbLoadImage("Space.bmp", SPACE_NUM);// space

		dbLoadMusic("1-Mute City.mp3", SPACE_MUSIC);
		dbLoopMusic(currentLevel);// use currentLevel also to change the track
		backSpeed = 6;
		break;

		// Level 2: Grassy Plain
	case 2:
		dbLoadImage("GrassyPlainCoords.bmp", GRASS_COORDS_NUM);
		dbSprite(GRASS_COORDS_NUM, 0, 0, GRASS_COORDS_NUM);
		dbWait(wait);

		dbDeleteSprite(GRASS_COORDS_NUM);
		dbDeleteImage(GRASS_COORDS_NUM);

		dbLoadImage("GrassyPlain.bmp", GLAND_NUM);// grassy plain

		dbLoadMusic("2-Venom.mp3", GRASS_MUSIC);
		dbLoopMusic(currentLevel);
		backSpeed = 8;
		break;

		// Level 3: Desert
	case 3:
		dbLoadImage("DesertCoords.bmp", DESERT_COORDS_NUM);
		dbSprite(DESERT_COORDS_NUM, 0, 0, DESERT_COORDS_NUM);
		dbWait(wait);

		dbDeleteSprite(DESERT_COORDS_NUM);
		dbDeleteImage(DESERT_COORDS_NUM);

		dbLoadImage("Desert.bmp", DLAND_NUM);// desert

		dbLoadMusic("3-Fire Emblem.mp3", DESERT_MUSIC);
		dbLoopMusic(currentLevel);
		backSpeed = 7;
		break;

		// Level 4: Above the Ocean
	case 4:
		dbLoadImage("AboveTheOceanCoords.bmp", OCEAN_COORDS_NUM);
		dbSprite(OCEAN_COORDS_NUM, 0, 0, OCEAN_COORDS_NUM);
		dbWait(wait);

		dbDeleteSprite(OCEAN_COORDS_NUM);
		dbDeleteImage(OCEAN_COORDS_NUM);

		dbLoadImage("AboveTheOcean.bmp", OCEAN_NUM);// ocean

		dbLoadMusic("4-Big Blue.mp3", OCEAN_MUSIC);
		dbLoopMusic(currentLevel);
		backSpeed = 8;
		break;

		// Level 5: Gelid World
	case 5:
		dbLoadImage("GelidWorldCoords.bmp", GELID_COORDS_NUM);
		dbSprite(GELID_COORDS_NUM, 0, 0, GELID_COORDS_NUM);
		dbWait(wait);

		dbDeleteSprite(GELID_COORDS_NUM);
		dbDeleteImage(GELID_COORDS_NUM);

		dbLoadImage("GelidWorld.bmp", ILAND_NUM);// gelid (ice) world

		dbLoadMusic("5-Mach Rider.mp3", GELID_MUSIC);
		dbLoopMusic(currentLevel);
		backSpeed = 7;
		break;

		// Level 6: Volcanic Expanse
	case 6:
		dbLoadImage("VolcanicExpanseCoords.bmp", VOL_COORDS_NUM);
		dbSprite(VOL_COORDS_NUM, 0, 0, VOL_COORDS_NUM);
		dbWait(wait);

		dbDeleteSprite(VOL_COORDS_NUM);
		dbDeleteImage(VOL_COORDS_NUM);

		dbLoadImage("VolcanicExpanse.bmp", LAVA_NUM);// volcanic expanse

		dbLoadMusic("6-Brinstar.mp3", VOL_MUSIC);
		dbLoopMusic(currentLevel);
		backSpeed = 7;
		break;

		// Level 7: Night Megalopolis
	case 7:
		dbLoadImage("MegalopolisCoords.bmp", MEGA_COORDS_NUM);
		dbSprite(MEGA_COORDS_NUM, 0, 0, MEGA_COORDS_NUM);
		dbWait(wait);

		dbDeleteSprite(MEGA_COORDS_NUM);
		dbDeleteImage(MEGA_COORDS_NUM);

		dbLoadImage("Megalopolis.bmp", MEGA_NUM);// megalopolis

		dbLoadMusic("7-Brinstar Depths.mp3", MEGA_MUSIC);
		dbLoopMusic(currentLevel);
		backSpeed = 8;
		break;

		// Level 8: Hyperspace
	case 8:
		dbLoadImage("HyperspaceCoords.bmp", HYPER_COORDS_NUM);
		dbSprite(HYPER_COORDS_NUM, 0, 0, HYPER_COORDS_NUM);
		dbWait(wait);

		dbDeleteSprite(HYPER_COORDS_NUM);
		dbDeleteImage(HYPER_COORDS_NUM);

		dbLoadImage("Hyperspace.bmp", HYPER_NUM);// hyperspace

		dbLoadMusic("8-Multi-Man Melee 2.mp3", HYPER_MUSIC);
		dbLoopMusic(currentLevel);
		backSpeed = 25;
		break;

		// Level 9: Alien World
	case 9:
		dbLoadImage("AlienWorldCoords.bmp", ALIEN_COORDS_NUM);
		dbSprite(ALIEN_COORDS_NUM, 0, 0, ALIEN_COORDS_NUM);
		dbWait(wait);

		dbDeleteSprite(ALIEN_COORDS_NUM);
		dbDeleteImage(ALIEN_COORDS_NUM);

		dbLoadImage("AlienWorld.bmp", ALIEN_W);// alien world

		dbLoadMusic("9-Multi-Man Melee 1.mp3", ALIEN_MUSIC);
		dbLoopMusic(currentLevel);
		backSpeed = 8;
		break;

		// Level 10: Emperor's Base
	case 10:
		dbLoadImage("EmperorBaseCoords.bmp", FORT_COORDS_NUM);
		dbSprite(FORT_COORDS_NUM, 0, 0, FORT_COORDS_NUM);
		dbWait(wait);

		dbDeleteSprite(FORT_COORDS_NUM);
		dbDeleteImage(FORT_COORDS_NUM);

		dbLoadImage("EmperorBase.bmp", ENEMY_FORT);// last enemy stronghold
		
		dbLoadMusic("10-Final Destination.mp3", ENEMY_FORT_MUSIC);
		dbLoopMusic(currentLevel);
		backSpeed = 2;
		break;
	}

	// Set this flag to false until boss is defeated
	scanLevel = false;

	dbSyncOn();// return to manual refresh
}
// Render Background Function ************************************
void renderLevel(int currentLevel, int &backX, int &backSpeed, int WIDTH, int &result)
{
	// Loop background
	dbSprite(currentLevel, backX, 0, currentLevel);
	backX -= backSpeed;// constantly move forward

	// Go back to beginning of looped space background
	if( backX < dbSpriteWidth(currentLevel) - dbSpriteWidth(currentLevel) * 2 + WIDTH )
	{
		backX = 0;// loop back to the beginning of level sprite
	}

	// Generate random number(for multiple purposes)
	result = dbRND(1200);
}
// The Player Ship Function **************************************
void playerShip(int &shipX, int &shipY, int &shipSpeed, int shipW, int shipH, int hTitleX, int hTitleY,
	int &hBarX, int &hBarY, int &healthW, bool &laserBlast, int &laserX, int &laserY, int &laserSpeed,
	int &health, int currentLevel, int WIDTH, int HEIGHT)
{
	// Move ship with directional keys ----------------------------------------------------------
	if( dbRightKey() )
	{
		shipX += shipSpeed;// go forward
	}
	if( dbLeftKey() )
	{
		shipX -= shipSpeed;// reverse
	}
	if( dbUpKey() )
	{
		shipY -= shipSpeed;// go up
	}
	if( dbDownKey() )
	{
		shipY += shipSpeed;// do down
	}

	// Then update ship sprite and related sprites ----------------------------------------------
	// Player ship itself
	dbShowSprite(SHIP_NUM);// now show sprite after coords screen
	dbSprite(SHIP_NUM, shipX, shipY, SHIP_NUM);
	// offset sprite (for good measure)
	dbOffsetSprite(SHIP_NUM, shipW/2, shipH/2);
	// Health bar and title
	dbSprite(HEALTH_TITLE_NUM, hTitleX, hTitleY, HEALTH_TITLE_NUM);// title sprite
	dbSprite(HEALTH_NUM, hBarX, hBarY, HEALTH_NUM);// bar itself
	dbSizeSprite(HEALTH_NUM, healthW, dbSpriteHeight(HEALTH_NUM));// resize according to health

	// Check for collisions with the screen border ----------------------------------------------
	if( shipX >= WIDTH - shipW/2 || shipX <= shipW/2 )
	{
		if( shipX >= WIDTH - shipW/2 )
		{
			shipX = WIDTH - shipW/2;
		}
		if( shipX <= shipW/2 )
		{
			shipX = shipW/2;
		}
	}
	if( shipY >= HEIGHT - shipH/2 || shipY <= shipH/2 )
	{
		if( shipY >= HEIGHT - shipH/2 )
		{
			shipY = HEIGHT - shipH/2;
		}
		if( shipY <= shipH/2 )
		{
			shipY = shipH/2;
		}
	}
	
	// The laser cannon -------------------------------------------------------------------------
	if( dbSpaceKey() )
	{
		laserBlast = true;// laser will shoot off now
	}
	if( laserBlast )
	{
		dbSprite(LASR_NUM, laserX, laserY, LASR_NUM);// show laser sprite
		laserX += laserSpeed;// away it goes

		if( laserX >= WIDTH - dbSpriteWidth(LASR_NUM) * 1/4 )
		{
			laserBlast = false;// "reset" blaster if laser exits screen
			dbDeleteSprite(LASR_NUM);// delete laser sprite so it doesn't interfere with anything else
		}
	}
	// Keep updating laser coords even if trigger isn't pressed
	if( !laserBlast )
	{
		laserX = shipX;
		laserY = shipY;
	}
	
	// When ship health reduces to zero, introduce the failure screen ---------------------------
	if( health <= 0 )
	{
		dbStopMusic(currentLevel);// stop playing current track for whatever level
		dbWait(1500);// wait for dramatic effect

		dbLoadMusic("11-FAIL-Challenger!.mp3", FAIL_MUSIC);// alarm
		dbPlayMusic(FAIL_MUSIC);
		dbSprite(FAIL_NUM, 0, 0, FAIL_NUM);// failure screen

		dbSync();// keep refreshing the screen

		dbEscapeKey();// end the game with the escape key
	}
}
// The Power-Ups Function ****************************************
void powerups(int result, bool &multiIcon, int &mulX, int &mulY, int WIDTH, int HEIGHT, bool &multiLaser,
	int &laserX, int &laserY, bool &laserBlast, int &laserFuel, bool &shipIcon, int &hyperShipX, int &hyperShipY,
	bool &shipHyper, int &shipSpeed, int &boost, bool &laserIcon, int &hyperLaserX, int &hyperLaserY,
	bool &laserHyper, int &laserSpeed, int &laserBoost)
{
	// Multi-laser ------------------------------------------------------------------------------
	// Power-up icon appears if result matches constant
	if( result == POWR_NUM )
	{
		multiIcon = true;// allow multi-laser power-up icon to fall down
	}
	// Icon is allowed to appear
	if( multiIcon )
	{
		dbSprite(POWR_NUM, mulX, mulY, POWR_NUM);// show icon
		mulY++;// keep going down the screen

		// If the icon drops below the screen
		if( mulY >= HEIGHT + dbSpriteHeight(POWR_NUM) )
		{
			multiIcon = false;
			mulX = dbRND(WIDTH * 3/4);// reset coords
			mulY = -100;
		}
	}
	// When the power-up icon needs to be gone
	else
	{
		mulX = dbRND(WIDTH * 3/4);// keep sprite out if player ship's bounds
		mulY = -100;
		dbSprite(POWR_NUM, mulX, mulY, POWR_NUM);
	}

	// If player ship acquires multi-laser power-up
	if( dbSpriteCollision(SHIP_NUM, POWR_NUM) )
	{
		mulX = dbRND(WIDTH * 3/4);// reset coords
		mulY = -100;
		dbSprite(POWR_NUM, mulX, mulY, POWR_NUM);

		multiIcon = false;// wait again for icon to appear
		multiLaser = true;// ship can now shoot multiple lasers
	}
	// Player ship can now shoot multiple lasers
	if( multiLaser )
	{
		// Clone laser sprites and then display
		dbCloneSprite(LASR_NUM, LASR_1);
		dbCloneSprite(LASR_NUM, LASR_2);

		// Shoot out multiple lasers with the space key
		dbSprite(LASR_1, laserX, laserY + 25, LASR_NUM);
		dbSprite(LASR_2, laserX, laserY - 25, LASR_NUM);

		// Delete clone sprites in the same fashion as the original laser
		if( !laserBlast )
		{
			dbDeleteSprite(LASR_1);
			dbDeleteSprite(LASR_2);
		}

		laserFuel--;// fuel for multi-laser cannon used
		if( laserFuel <= 0 )// no more multilaser if fuel is all used up
		{
			dbDeleteSprite(LASR_1);// take out sprites to eliminate hitbox
			dbDeleteSprite(LASR_2);

			laserFuel = 350;// restore fuel value if icon is picked up again
			multiLaser = false;// ship cannot shoot multiple lases for the time being
		}
	}
	
	// Hyper Ship -------------------------------------------------------------------------------
	// Power-up icon appears if result matches constant
	if( result == HYPR_SHIP_NUM )
	{
		shipIcon = true;// allow icon to appear
	}
	// Icon is allowed to appear
	if( shipIcon )
	{
		dbSprite(HYPR_SHIP_NUM, hyperShipX, hyperShipY, HYPR_SHIP_NUM);
		hyperShipY++;// icon travels down

		// If the icon drops below the screen
		if( hyperShipY >= HEIGHT + dbSpriteHeight(HYPR_SHIP_NUM) )
		{
			shipIcon = false;
			hyperShipX = dbRND(WIDTH * 3/4);
			hyperShipY = -100;
		}
	}
	// When the power-up icon needs to be gone
	else
	{
		hyperShipX = dbRND(WIDTH * 3/4);// keep sprite out if player ship's bounds
		hyperShipY = -100;
		dbSprite(HYPR_SHIP_NUM, hyperShipX, hyperShipY, HYPR_SHIP_NUM);
	}

	// If player ship acquires this power-up
	if( dbSpriteCollision(SHIP_NUM, HYPR_SHIP_NUM) )
	{
		hyperShipX = dbRND(WIDTH * 3/4);// reset coords
		hyperShipY = -100;
		dbSprite(HYPR_SHIP_NUM, hyperShipX, hyperShipY, HYPR_SHIP_NUM);

		shipIcon = false;// wait again for icon to appear
		shipHyper = true;// player ship can move at a faster speed
	}

	// Player ship can move at a higher speed
	if( shipHyper )
	{
		shipSpeed = 13;// set how fast player ship can go
		boost--;// reduce boost the player ship has

		// When boost runs out
		if( boost <= 0 )
		{
			shipSpeed = 6;// reset ship speed

			boost = 400;// reset boost value
			shipHyper = false;// ship cannot go at high speeds for the meantime
		}
	}
	else// when power-up needs to be deactivated
	{
		shipSpeed = 6;// reset ship speed
		boost = 400;// reset boost value (just in case)
	}

	// Hyper Lasers -----------------------------------------------------------------------------
	if( result == HYPR_LSR_NUM )
	{
		laserIcon = true;// allow icon to appear
	}
	// Icon is allowed to appear
	if( laserIcon )
	{
		dbSprite(HYPR_LSR_NUM, hyperLaserX, hyperLaserY, HYPR_LSR_NUM);
		hyperLaserY++;// icon travels down

		// If the icon drops below the screen
		if( hyperLaserY >= HEIGHT + dbSpriteHeight(HYPR_LSR_NUM) )
		{
			laserIcon = false;
			hyperLaserX = dbRND(WIDTH * 3/4);
			hyperLaserY = -100;
		}
	}
	// When the power-up icon needs to be gone
	else
	{
		hyperLaserX = dbRND(WIDTH * 3/4);// keep sprite out if player ship's bounds
		hyperLaserY = -100;
		dbSprite(HYPR_LSR_NUM, hyperLaserX, hyperLaserY, HYPR_LSR_NUM);
	}

	// If player ship acquires this power-up
	if( dbSpriteCollision(SHIP_NUM, HYPR_LSR_NUM) )
	{
		hyperLaserX = dbRND(WIDTH * 3/4);// reset coords
		hyperLaserY = -100;
		dbSprite(HYPR_LSR_NUM, hyperLaserX, hyperLaserY, HYPR_LSR_NUM);

		laserIcon = false;// wait again for icon to appear
		laserHyper = true;// lasers can move at a faster speed
	}

	// Lasers now move at a higher speed
	if( laserHyper )
	{
		laserSpeed = 57;// increase laser speed
		laserBoost--;// reduce boost the player ship has

		// When boost runs out
		if( laserBoost <= 0 )
		{
			laserSpeed = 27;// reset ship speed

			laserBoost = 250;// reset boost value
			laserHyper = false;// ship cannot go at high speeds for the meantime
		}
	}
	else// when power-up needs to be deactivated
	{
		laserSpeed = 27;// reset ship speed
		laserBoost = 250;// reset boost value (just in case)
	}
}
// The Regular Enemy Function ************************************
void regularEnemy(int WIDTH, int HEIGHT, int result, int hit, int enemySpeed, int enemyLaserSpeed, int &shipX, 
	int &shipY, int &health, int &healthW, int &deathToll, bool &laserBlast, bool &enemy1Appear, int &enemy1X, 
	int &enemy1Y, bool &enemy1Shoot, bool &enemy1Laser, int &enemy1LaserX, int &enemy1LaserY, int enemyOne, 
	int enemyOneLaser)
{
	// Entire enemy mechanics are in this one if statement, in case it needs to be turned off
	if( enemy1Appear )// determine if enemy can appear (like in the case of a boss battle)
	{
		// Enemy movement ---------------------------------------------------------------------------
		dbSprite(enemyOne, enemy1X, enemy1Y, ENEM_NUM);// show then center sprite (keep image num)
		dbOffsetSprite(enemyOne, dbSpriteWidth(enemyOne)/2, dbSpriteHeight(enemyOne)/2);// center sprite
		enemy1X -= enemySpeed;// go left at a certain speed
				
		if( enemy1X <= 0 )// enemy goes off the left side of the screen
		{
			enemy1X = WIDTH + 50;// reset enemy x position
			enemy1Y = dbRND(HEIGHT);// randomize y coord every time

			// Penalize the player for not shooting down the enemy in time
			health--;
			healthW -= hit;
		}

		// Regular enemy laser components -----------------------------------------------------------
		if( enemy1Shoot )// determine if enemy will shoot laser based on random number
		{
			if( result <= enemyOneLaser )
			{
				enemy1Laser = true;// enemy laser will appear
			}
		}
		// Enemy shoots laser
		if( enemy1Laser )
		{
			dbSprite(enemyOneLaser, enemy1LaserX, enemy1LaserY, ELSR_NUM);// show enemy laser sprite (keep image num)
			dbOffsetSprite(enemyOneLaser, dbSpriteWidth(enemyOneLaser), dbSpriteHeight(enemyOneLaser));// offset laser sprite
			enemy1LaserX -= enemyLaserSpeed;// away it goes

			if( enemy1LaserX <= -75 )
			{
				enemy1Laser = false;// "reset" blaster if laser exits screen
				dbDeleteSprite(enemyOneLaser);// delete laser sprite so it doesn't interfere with anything else
			}
		}
		// Keep updating laser coords for enemy
		if( !enemy1Laser )
		{
			enemy1LaserX = enemy1X;
			enemy1LaserY = enemy1Y;
		}

		// Player ship is hit by a regular enemy laser ----------------------------------------------
		// Enemy shoots player ship
		if( dbSpriteExist(enemyOneLaser) )
		{
			if( dbSpriteCollision(enemyOneLaser, SHIP_NUM) )
			{
				enemy1Laser = false;// reset enemy trigger
				dbDeleteSprite(enemyOneLaser);// delete laser sprite
				health--;
				healthW -= hit;
			}
		}

		// Enemy hit by any of the player ship lasers -------------------------------------------
		if( dbSpriteCollision(LASR_NUM, enemyOne) || dbSpriteCollision(LASR_1, enemyOne) || dbSpriteCollision(LASR_2, enemyOne) )
		{
			laserBlast = false;// "reset" ship blaster
			enemy1Laser = false;// "reset" enemy blaster

			dbDeleteSprite(LASR_NUM);// delete ship laser sprite
			dbDeleteSprite(enemyOneLaser);// delete enemy laser sprite (takes into account specific enemy)

			// Delete enemy sprite in any case
			dbDeleteSprite(enemyOne);

			// Reset coords
			enemy1X = WIDTH + 150;
			enemy1Y = dbRND(HEIGHT);

			deathToll--;// increase number of enemy deaths
		}

		// Player ship crashes with Enemy One -------------------------------------------------------
		if( dbSpriteCollision(enemyOne, SHIP_NUM) )
		{
			health--;
			healthW -= hit;
					
			shipX = WIDTH * 1/4;
			shipY = HEIGHT/2;
		}
	}
	else
	{
		// Delete all enemy-related sprites
		if( dbSpriteExist(enemyOne) )
		{
			dbDeleteSprite(enemyOne);
		}
		if( dbSpriteExist(enemyOneLaser) )
		{
			dbDeleteSprite(enemyOneLaser);
		}
	}
}
// The Level Boss Function ***************************************
void levelBoss(int bTitleX, int bTitleY, int bossSpeed, int WIDTH ,int HEIGHT, int result, int hit, int bossHit, 
	int requiredStrikes, int bossLaserSpeed, int &deathToll, int &bossX, int &bossY, int &bBarX, int &bBarY, 
	int &bossHealthW, int &bossLaserX, int &bossLaserY, int &currentLevel, int &health, int &healthW, int &shipX, 
	int &shipY, int &bossHealth, bool &enemy1Appear, bool &enemy2Appear, bool &enemy3Appear, bool &bossAppear, 
	bool &bossLaser, bool &laserBlast, bool &multiIcon, bool &multiLaser, bool &shipIcon, bool &shipHyper, 
	bool &laserIcon, bool &laserHyper, bool &scanLevel, bool &bossMoveUp)
{
	// Disable regular enemies and allow level boss to appear --------------------------------------
	if( deathToll < 0 )
	{
		// Regular Enemies will not appear or shoot
		enemy1Appear = false;
		enemy2Appear = false;
		enemy3Appear = false;

		bossAppear = true;
	}

	// The level boss appears
	if( bossAppear )
	{
		// Level Boss movement ----------------------------------------------------------------------
		dbSprite(LVL_BOSS_NUM, bossX, bossY, LVL_BOSS_NUM);// display and center sprite
		dbOffsetSprite(LVL_BOSS_NUM, dbSpriteWidth(LVL_BOSS_NUM)/2, dbSpriteHeight(LVL_BOSS_NUM)/2);

		// Level boss health bar and title
		dbSprite(BOSS_HEALTH_TITLE, bTitleX, bTitleY, BOSS_HEALTH_TITLE);// place boss title above bar
		dbSprite(BOSS_HEALTH_NUM, bBarX, bBarY, BOSS_HEALTH_NUM);// bar and re-sizing
		dbSizeSprite(BOSS_HEALTH_NUM, bossHealthW, dbSpriteHeight(BOSS_HEALTH_NUM));// resize accodring to health

		// Play music specific for level boss encounter
		dbStopMusic(currentLevel);
		dbLoopMusic(BOSS_MUSIC);
				
		// Level boss moves up and down
		if( bossMoveUp )
		{
			bossY -= bossSpeed;// move up at vertical speed
			if( bossY <= 0 )// when boss ascends too high, drop
			{
				bossMoveUp = false;// now begin to move down
			}
		}	
		else
		{
			bossY += bossSpeed;// move down
			if( bossY >= HEIGHT )// when boss drops too low, ascend
			{
				bossMoveUp = true;// now begin to move up
			}
		}

		// Level boss laser components --------------------------------------------------------------
		if( result >= LB_LSR_NUM )
		{
			bossLaser = true;// boss shoots and laser appears
		}

		if( bossLaser )
		{
			dbSprite(LB_LSR_NUM, bossLaserX, bossLaserY, LB_LSR_NUM);
			bossLaserX -= bossLaserSpeed;// laser blasts off

			if( bossLaserX <= -75 )
			{
				bossLaser = false;// "reset" boss laser/trigger
				dbDeleteSprite(LB_LSR_NUM);// delete sprite when out of bounds
			}
		}
		// Keep updating laser coords for level boss
		if( !bossLaser )
		{
			bossLaserX = bossX;
			bossLaserY = bossY;
		}

		// Player ship takes damage -----------------------------------------------------------------
		// Player is hit by level boss laser
		if( dbSpriteExist(LB_LSR_NUM) )
		{
			if( dbSpriteCollision(LB_LSR_NUM, SHIP_NUM) )
			{
				health--;
				healthW -= hit;
			}
		}
		// Player ship is destroyed on impact
		if( dbSpriteCollision(LVL_BOSS_NUM, SHIP_NUM) )
		{
			health--;
			healthW -= hit;
					
			shipX = WIDTH * 1/4;
			shipY = HEIGHT/2;
		}

		// Ship laser hits level boss ---------------------------------------------------------------
		if( dbSpriteCollision( LASR_NUM, LVL_BOSS_NUM ) || dbSpriteCollision( LASR_1, LVL_BOSS_NUM ) || 
			dbSpriteCollision( LASR_2, LVL_BOSS_NUM ) )
		{
			bossHealth--;// decrement actual health value
			bossHealthW -= bossHit;// decrease size of health bar

			// Make sure to delete all three laser sprites
			dbDeleteSprite(LASR_NUM);
			dbDeleteSprite(LASR_1);
			dbDeleteSprite(LASR_2);
		}
				
		// Level Boss is defeated -------------------------------------------------------------------
		if( bossHealth <= 0 )
		{
					
			// Reset level boss components --------------------------------------------------------------
			dbDeleteSprite(LVL_BOSS_NUM);// level boss itself
			dbDeleteSprite(LB_LSR_NUM);// its laser also
			dbDeleteSprite(BOSS_HEALTH_NUM);// its now stretched health bar
			dbDeleteSprite(BOSS_HEALTH_TITLE);// and health title

			bossX = WIDTH;// reset boss coords
			bossY = HEIGHT/2;
			bossHealth = 100;// reset health value
			bossHealthW = 500;// re-instate health bar width

			// Reset player ship mechanics --------------------------------------------------------------
			dbDeleteSprite(SHIP_NUM);// player ship
			dbDeleteSprite(LASR_NUM);// all three lasers
				dbDeleteSprite(LASR_1);
				dbDeleteSprite(LASR_2);
			dbDeleteSprite(HEALTH_NUM);// health bar
			dbDeleteSprite(HEALTH_TITLE_NUM);// health bar title
			laserBlast = false;// "reset" trigger

			health = 35;// reset health value
			healthW = 350;// re-instate bar width

			int shipX = WIDTH * 1/4;// re-assign starting x & y coords
			int shipY = HEIGHT/2;

			// Disable power-ups ------------------------------------------------------------------------
			dbDeleteSprite(POWR_NUM);// multi-laser
			multiIcon = false;// ensure icons don't appear outside gameplay
			multiLaser = false;// abilities turned off before level starts
			dbDeleteSprite(HYPR_SHIP_NUM);// hyper ship
			shipIcon = false;
			shipHyper = false;
			dbDeleteSprite(HYPR_LSR_NUM);// hyper laser
			laserIcon = false;
			laserHyper = false;

			// Enemies will reappear again --------------------------------------------------------------
			bossAppear = false;// make sure boss doesn't appear until needed again
			dbStopMusic(BOSS_MUSIC);// stop level boss track

			deathToll = requiredStrikes;// reset death toll
			enemy1Appear = true;// regular enemies will attack once again
			enemy2Appear = true;
			enemy3Appear = true;

			// Move on to the next level ----------------------------------------------------------------
			scanLevel = true;// increment currentLevel
			currentLevel++;// now move on to next level
					
		}
	}
}
// The Emperor Function ******************************************
void theEmperor(int currentLevel, int deathToll, int emperorSpeed, int WIDTH, int HEIGHT, int result, 
	int emperorSmallLaserSpeed, int emperorBigLaserSpeed, int hit, int emperorHit, int eTitleX, int eTitleY, 
	int eBarX, int eBarY, int &emperorX, int &emperorY, int &backSpeed, int &emperorHealthW, 
	int &emperorSmallLaserX, int &emperorSmallLaserY, int &emperorBigLaserX, int &emperorBigLaserY, 
	int &health, int &healthW, int &emperorHealth, bool &enemy1Appear, bool &enemy2Appear, bool &enemy3Appear, 
	bool &emperorAppear, bool &emperorMoveH, bool &emperorMoveV, bool &emperorMoveUp, bool &emperorSmallLaser, 
	bool &emperorBigLaser, bool &multiIcon, bool &multiLaser, bool &shipIcon, bool &shipHyper, bool &laserIcon, 
	bool &laserHyper)
{
	// Conditions met for emperor to appear -----------------------------------------------------
	if( currentLevel == 10 && deathToll == 2 )
	{
		// Disable enemy mechanics
		if( enemy1Appear || enemy2Appear || enemy3Appear )
		{
			enemy1Appear = false;
			enemy2Appear = false;
			enemy3Appear = false;
		}
		// Allow the emperor to appear
		emperorAppear = true;

		dbStopMusic(currentLevel);// stop music, and load emperor's track
		dbLoadMusic("11-EMPEROR-Metroid Prime Boss Theme.mp3", EMPEROR_MUSIC);
	}

	// This if statement will contain the rest of the emperor mechanics -------------------------
	if( emperorAppear )
	{
		// emulate the level boss code, take a pic of its code and/or copy it here
		dbSprite(EMPEROR_NUM, emperorX, emperorY, EMPEROR_NUM);// display and center sprite
		dbOffsetSprite(EMPEROR_NUM, dbSpriteWidth(EMPEROR_NUM)/2, dbSpriteHeight(EMPEROR_NUM)/2);

		// Emperor movement mechanics ---------------------------------------------------------------
		// Emperor initially moves horizontally
		if( emperorMoveH )
		{
			emperorX -= emperorSpeed;// move forward

			dbLoopMusic(EMPEROR_MUSIC);// play emperor's track
					 
			// Emperor stops after a certain point
			if( emperorX <= WIDTH )
			{
				emperorMoveH = false;// stop moving horizontally
				emperorMoveV = true;// begin moving up and down

				backSpeed = 45;// increase looping speed
			}
		}
		// Emperor moves up and down
		if( emperorMoveUp )
		{
			emperorY -= emperorSpeed;// move up
			if( emperorY <= 0 )// when emperor ascends too high, drop
			{
				emperorMoveUp = false;// now begin to move down
			}
		}	
		else
		{
			emperorY += emperorSpeed;// move down
			if( emperorY >= HEIGHT )// when emperor drops too low, ascend
			{
				emperorMoveUp = true;// now begin to move up
			}
		}
		// Emperor health mechanics -----------------------------------------------------------------
		// Display and center health title
		dbSprite(EMP_HEALTH_BT_NUM, eTitleX, eTitleY, EMP_HEALTH_BT_NUM);
		dbOffsetSprite(EMP_HEALTH_BT_NUM, dbSpriteWidth(EMP_HEALTH_BT_NUM)/2, dbSpriteHeight(EMP_HEALTH_BT_NUM)/2);
		// Display and center health bar
		dbSprite(EMP_HEALTH_BAR_NUM, eBarX, eBarY, EMP_HEALTH_BAR_NUM);
		dbOffsetSprite(EMP_HEALTH_BAR_NUM, dbSpriteWidth(EMP_HEALTH_BAR_NUM)/2, dbSpriteHeight(EMP_HEALTH_BAR_NUM)/2);
		dbSizeSprite(EMP_HEALTH_BAR_NUM, emperorHealthW, dbSpriteHeight(EMP_HEALTH_BAR_NUM));// resize accordingly

		// Small laser mechanics --------------------------------------------------------------------
		if( result >= EMPEROR_NUM/2 )
		{
			emperorSmallLaser = true;// emperor can now shoot laser
		}

		if( emperorSmallLaser )
		{
			// Display and center laser sprite
			dbSprite(EMP_SLSR_NUM, emperorSmallLaserX, emperorSmallLaserY, EMP_SLSR_NUM);
			dbOffsetSprite(EMP_SLSR_NUM, dbSpriteWidth(EMP_SLSR_NUM)/2, dbSpriteHeight(EMP_SLSR_NUM)/2);
			emperorSmallLaserX -= emperorSmallLaserSpeed;// laser blasts off

			if( emperorSmallLaserX <= -1 * dbSpriteWidth(EMP_SLSR_NUM) )
			{
				emperorSmallLaser = false;// "reset" boss laser/trigger for laser
				dbDeleteSprite(EMP_SLSR_NUM);// delete laser sprite when out of bounds
			}
		}
		// Keep updating laser coords for level boss
		if( !emperorSmallLaser )
		{
			emperorSmallLaserX = emperorX;
			emperorSmallLaserY = emperorY;
		}

		// Big laser mechanics ----------------------------------------------------------------------
		if( result == EMP_SLSR_NUM || result == EMP_LSR_NUM || result == EMP_HEALTH_BAR_NUM
			|| result == EMP_HEALTH_BT_NUM )
		{
			emperorBigLaser = true;// emperor can now shoot big laser
		}

		if( emperorBigLaser )
		{
			// Display and center big laser sprite
			dbSprite(EMP_LSR_NUM, emperorBigLaserX, emperorBigLaserY, EMP_LSR_NUM);
			dbOffsetSprite(EMP_LSR_NUM, dbSpriteWidth(EMP_LSR_NUM)/2, dbSpriteHeight(EMP_LSR_NUM)/2);
			emperorBigLaserX -= emperorBigLaserSpeed;// big laser blasts off

			if( emperorBigLaserX <= -1 * dbSpriteWidth(EMP_LSR_NUM) )
			{
				emperorBigLaser = false;// "reset" boss laser/trigger for big laser
				dbDeleteSprite(EMP_LSR_NUM);// delete big laser sprite when out of bounds
			}
		}
		// Keep updating laser coords for level boss
		if( !emperorBigLaser )
		{
			emperorBigLaserX = emperorX;
			emperorBigLaserY = emperorY;
		}

		// Player ship takes damage -----------------------------------------------------------------
		// Small laser
		if( dbSpriteExist(EMP_SLSR_NUM) )
		{
			if( dbSpriteCollision(EMP_SLSR_NUM, SHIP_NUM) )
			{
				health--;
				healthW -= hit;
			}
		}
		// Big laser
		if( dbSpriteExist(EMP_LSR_NUM) )
		{
			if( dbSpriteCollision(EMP_LSR_NUM, SHIP_NUM) )
			{
				health -= 2;// reduce health by 3, not 1
				healthW -= hit * 2;// reduce health bar 3x
			}
		}
		// Player ship is destroyed by emperor on impact
		if( dbSpriteCollision(EMPEROR_NUM, SHIP_NUM) )
		{
			healthW = 1;
			health = 0;// reduce health
		}

		// Ship laser hits the emperor --------------------------------------------------------------
		if( dbSpriteCollision( LASR_NUM, EMPEROR_NUM ) || dbSpriteCollision( LASR_1, EMPEROR_NUM ) || 
			dbSpriteCollision( LASR_2, EMPEROR_NUM ) )
		{
			emperorHealth--;// decrement actual health value
			emperorHealthW -= emperorHit;// decrease size of health bar

			// Make sure to delete all three laser sprites
			dbDeleteSprite(LASR_NUM);
			dbDeleteSprite(LASR_1);
			dbDeleteSprite(LASR_2);
		}

		// When the emperor is defeated, load success screen ----------------------------------------
		if( emperorHealth <= 0 )
		{
			// Disable character mechanics --------------------------------------------------------------
			// Disable player ship mechanics
			dbDeleteSprite(SHIP_NUM);
			dbDeleteSprite(LASR_NUM);
			dbDeleteSprite(LASR_1);
			dbDeleteSprite(LASR_2);

			// Disable power-ups
			dbDeleteSprite(POWR_NUM);// multi-laser
			multiIcon = false;// ensure icons don't appear anymore
			multiLaser = false;// abilities turned off for good
			dbDeleteSprite(HYPR_SHIP_NUM);// hyper ship
			shipIcon = false;
			shipHyper = false;
			dbDeleteSprite(HYPR_LSR_NUM);// hyper laser
			laserIcon = false;
			laserHyper = false;

			// Regular enemies and level boss already disabled from appearing

			// Disable emperor mechanics
			emperorAppear = false;
			dbDeleteSprite(EMPEROR_NUM);// delete emperor sprite
			// Delete emperor small and big laser sprite
			dbDeleteSprite(EMP_SLSR_NUM);
			dbDeleteSprite(EMP_LSR_NUM);

			// Success! ---------------------------------------------------------------------------------
			dbStopMusic(EMPEROR_MUSIC);// stop emperor track
			dbWait(3000);// wait 3 secs

			// Play success music (once)
			dbLoadMusic("11-SUCC-Poke Floats.mp3", SUCC_MUSIC);
			dbPlayMusic(SUCC_MUSIC);

			// Display success screen
			dbSprite(SUCC_NUM, 0, 0, SUCC_NUM);

			dbSync();// keep refreshing the screen

			// Press the escape key to finish the game :)
			dbEscapeKey();
		}
	}
}
// ***************************************************************