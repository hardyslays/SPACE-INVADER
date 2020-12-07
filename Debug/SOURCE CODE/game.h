#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "player.h"
#include "bullet.h"
#include "Enemy.h"
#include <time.h>
#include <string>
#include <sstream>

class Game
{
private:
	//WINDOW
	sf::RenderWindow* app;

	//RESOURCES
	std::map<std::string, sf::Texture*> textures;
	std::vector<bullet*> bullets;
	bool isStart;

	//GUI
	sf::Font font;
	unsigned int points;
	sf::Text text;
	sf::Text gameOver;
	sf::Text restart;
	sf::Text welcomeText;
	sf::Text start;

	//BACKGROUND
	sf::Texture bgTex;
	sf::Sprite Bg;

	//PLAYER
	player* p1;
	float acc, drag;
	sf::Vector2f vel, maxVel;

	//PLAYER GUI
	sf::RectangleShape hpBar;
	sf::RectangleShape maxHpBar;


	//ENEMIES
	std::vector<Enemy*> enemies;
	float enemySpawnTimer;
	float spawnTimerMax;
	sf::Vector2f enemySpawnPos;

	//PRIVATE FUNCTIONS
	void initapp();
	void welcome();
	void initGUI();
	void initWorld();
	void initTextures();
	void initplayer();
	void initEnemies();

	void Restart();

public:
	Game();
	virtual ~Game(); 

	//FUNCTIONS
	
	//UPDATE FUNCTIONS
	void updatePollEvent();
	void updateInput();
	void updateGUI();
	void updateCollision();
	void updateBullet();
	void updateEnemies();
	void update();

	//RENDER FUNCTIONS
	void renderGUI();
	void renderWorld();
	void render();

	//FUNCTION FOR RUNNING THE GAME
	void run();
};

