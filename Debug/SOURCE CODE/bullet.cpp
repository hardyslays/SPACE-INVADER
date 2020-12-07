#include "bullet.h"

bullet::bullet()
{

}

bullet::bullet(sf::Texture &tex, sf::Vector2f pos, float dir_x, float dir_y, float s)
{
	t = &tex;
	if (!this->t->loadFromFile("textures/bullet.png"))std::cout << "CANNOT LOAD BULLET TEXTURE.\n";
	t->setSmooth(true);
	this->sprite.setTexture(*t); 
	this->sprite.setScale(0.1, 0.1);
	this->sprite.setPosition(pos);
	this->dir.x = dir_x;
	this->dir.y = dir_y;
	this->speed = s;
}

bullet::~bullet()
{

}

const sf::FloatRect bullet::getBounds()
{
	return this->sprite.getGlobalBounds();
}

void bullet::update()
{
	this->sprite.move(this->speed * this->dir);
}

void bullet::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
