#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <iostream>	

class player
{
private:
	//CHARACTERSTICS OF PLAYER
	int hp;
	int hpMax;
	sf::Sprite sprite;
	sf::Texture tex;
	float speed;

	//PLAYER SHOOTING TIME
	float coolDown, coolDownMax;

	//PRIVATE FUNCTIONS
	void initVariables();
	void initTex();
	void initSprite();

public:
	player();
	virtual ~player();

	//FUNCTIONS

	//GETTING PLAYER INFO
	const sf::Vector2f getpos();
	const sf::FloatRect getBounds();
	const int getHp();
	const int getMaxHp();

	//MODIFYING PLAYER INFO
	void resetHp();
	void takeDamage(int dam);
	void setPos(sf::Vector2f pos);
	void move(float x, float y);

	//UTILITY FUNCTIONS
	bool canAttack();
	void updateAttack();
	void update();
	void render(sf::RenderTarget &target);
};

