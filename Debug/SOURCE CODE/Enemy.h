#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <iostream>	


class Enemy
{
	//TYPE OF ENEMY
	int type;

	//CHARACTERISTICS OF ENEMY
	sf::Texture tex;
	sf::Sprite sprite;
	int hp;
	int hpMax;
	int damage;
	int points;
	float xMotion;

	//PRIVATE FUNCTIONS
	void initVariable();
	void initTexture(const char* img);
	void initShape();

public:
	Enemy();
	Enemy(sf::Vector2f pos, float x);
	~Enemy();

	//GET ENEMY DETAILS
	const sf::FloatRect getBounds();
	int getPoint();
	int getHP();

	//MODIFY ENEMY DETAILS
	void takeDamage(int dam);
	int giveDamage();
	void update();
	void render(sf::RenderTarget* target);
};

