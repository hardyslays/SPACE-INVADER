#include "Enemy.h"


void Enemy::initVariable()
{
	int t;
	t = rand() % 10;

	if (t < 4 + rand() % 3)
	{
		type = 1;
		hpMax = 20;
		hp = this->hpMax;
		damage = 5;
		points = 10;
		initTexture("textures/enemyship1.png");
	}
	else if (t < 7 + rand() % 3)
	{
		type = 2;
		hpMax = 30;
		hp = this->hpMax;
		damage = 10;
		points = 20;
		initTexture("textures/enemyship2.png");
	}
	else
	{
		type = 3;
		hpMax = 50;
		hp = this->hpMax;
		damage = 15;
		points = 50;
		initTexture("textures/megaenemyship.png");
	}
}


void Enemy::initTexture(const char* img)
{
	if (!this->tex.loadFromFile(img))std::cout << "CANNOT LOAD ENEMY SHIP TEXTURE.\n";
	tex.setSmooth(true);

}


void Enemy::initShape()
{
	sprite.setTexture(tex);
	sprite.setScale(0.2 * type, 0.2 * type);
}

Enemy::Enemy()
{

}

Enemy::Enemy(sf::Vector2f pos,float x)
{
	this->xMotion = (300.f + rand() % (int)x ) * 0.0015f;
	this->xMotion = (rand() % 2) ? this->xMotion : -this->xMotion;
	this->initVariable();
	this->initShape();

	sprite.setPosition(pos);
}

Enemy::~Enemy()
{
	this->initVariable();
	this->initShape();

	sprite.setPosition(0.f, 0.f);
}

const sf::FloatRect Enemy::getBounds()
{
	return this->sprite.getGlobalBounds();
}

int Enemy::getPoint()
{
	return this->points;
}

void Enemy::takeDamage(int dam)
{
	hp -= dam;
	if (hp < 0) hp = 0;
}

int Enemy::getHP()
{
	return this->hp;
}

int Enemy::giveDamage()
{
	return damage;
}

void Enemy::update()
{

	this->sprite.move(xMotion, 7.f);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
