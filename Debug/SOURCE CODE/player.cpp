#include "player.h"

void player::initVariables()
{
	this->hpMax = 100;
	this->hp = this->hpMax;
	this->speed = 3.f;
	this->coolDownMax = 5.f;
	this->coolDown = this->coolDownMax;
}

void player::initTex()
{
	if (!this->tex.loadFromFile("textures/spaceship.png"))
		std::cout << "ERROR: SHIP TEXTURE COULD NOT BE LOADED FROM FILE.\n";
}

void player::initSprite()
{
	//SET TEXTURE TO THE SPRITE
	this->sprite.setTexture(this->tex);
	this->sprite.scale(0.3f, 0.3f);
}

player::player()
{
	this->initVariables();
	this->initTex();
	this->initSprite();
}

player::~player()
{

}

const sf::Vector2f player::getpos()
{
	return this->sprite.getPosition();
}

const sf::FloatRect player::getBounds()
{
	return this->sprite.getGlobalBounds();
}

const int player::getHp()
{
	return this->hp;
}

const int player::getMaxHp()
{
	return this->hpMax;
}

void player::resetHp()
{
	this->hp = this->hpMax;
}

void player::takeDamage(int dam)
{
	this->hp -= dam;
	if (hp < 0)hp = 0;
}

void player::setPos(sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void player::move(float x, float y)
{
	this->sprite.move(speed * x, speed * y);
}

bool player::canAttack()
{
	if (this->coolDown >= this->coolDownMax)
	{
		this->coolDown = 0.f;
		return true;
	}
	return false;
}

void player::updateAttack()
{
	if(this->coolDown < this->coolDownMax)
		this->coolDown += 1.f;
}

void player::update()
{
	this->updateAttack();

}

void player::render(sf::RenderTarget &target)
{
	target.draw(this->sprite);
}