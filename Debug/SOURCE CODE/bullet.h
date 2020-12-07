#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <iostream>

class bullet
{
	//BULLET CHARACTERISTICS
	sf::Texture* t;
	sf::Sprite sprite;
	sf::Vector2f dir;
	float speed;

public:
	bullet();
	bullet(sf::Texture &tex,sf::Vector2f pos, float dir_x, float dir_y, float speed);
	virtual ~bullet();

	//FUNCTIONS
	const sf::FloatRect getBounds();
	void update();
	void render(sf::RenderTarget* target);

};

