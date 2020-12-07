#include "game.h"

void Game::initapp()
{
	this->app = new sf::RenderWindow(sf::VideoMode(1920, 1080), "SPACE INVADERS!", sf::Style::Default);
	this->app->setFramerateLimit(60);
	this->app->setVerticalSyncEnabled(false);
}

void Game::initGUI()
{
	if (!this->font.loadFromFile("fonts/roboto.ttf"))std::cout << "ERROR LOADING FONT STYLE.\n";
	
	this->text.setFont(this->font);
	this->text.setCharacterSize(60);
	this->text.setFillColor(sf::Color::White);
	this->text.setPosition(this->app->getSize().x - 400.f, 10.f);

	this->gameOver.setFont(this->font);
	this->gameOver.setCharacterSize(100);
	this->gameOver.setFillColor(sf::Color::Red);
	this->gameOver.setString("GAME OVER!!!");
	this->gameOver.setPosition(this->app->getSize().x/2.f - this->gameOver.getGlobalBounds().width/2.f - 10.f, this->app->getSize().y / 2.f - this->gameOver.getGlobalBounds().height / 2.f - 20.f);

	this->restart.setFont(this->font);
	this->restart.setCharacterSize(60);
	this->restart.setFillColor(sf::Color::White);
	this->restart.setString("PRESS \"ENTER\" TO RESTART THE GAME OR \"ESC\" TO EXIT");
	this->restart.setPosition(this->app->getSize().x / 2.f - this->restart.getGlobalBounds().width / 2.f, this->app->getSize().y / 2.f - this->restart.getGlobalBounds().height / 2.f + 100.f);

	this->welcomeText.setFont(this->font);
	this->welcomeText.setCharacterSize(100);
	this->welcomeText.setFillColor(sf::Color::Color::Green);
	this->welcomeText.setString("\t\t\tSPACE INVADER\nTHE SAVIOUR OF THE SPACE");
	this->welcomeText.setPosition(this->app->getSize().x / 2.f - this->welcomeText.getGlobalBounds().width / 2.f - 30.f, this->app->getSize().y / 2.f - this->welcomeText.getGlobalBounds().height / 2.f - 50.f);

	this->start.setFont(this->font);
	this->start.setCharacterSize(50);
	this->start.setFillColor(sf::Color::Black);
	this->start.setString("PRESS \"ENTER\" TO start THE GAME OR \"ESC\" TO EXIT");
	this->start.setPosition(this->app->getSize().x / 2.f - this->start.getGlobalBounds().width / 2.f, this->app->getSize().y / 2.f - this->start.getGlobalBounds().height / 2.f + 100.f);

	this->hpBar.setSize(sf::Vector2f(450.f, 30.f));
	this->hpBar.setFillColor(sf::Color::Green);
	this->hpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->maxHpBar = this->hpBar;
	this->maxHpBar.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
	if (!this->bgTex.loadFromFile("textures/background.png"))
		std::cout << "ERROR LOADING BACKGROUND TEXTURE.\n";

	this->Bg.setTexture(this->bgTex);

}


void Game::welcome()
{
	app->clear();
	app->draw(this->Bg);
	app->draw(this->welcomeText);
	app->draw(this->start);
	this->app->display();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))isStart = 1;
}

void Game::initTextures()
{
	this->textures["bullet"] = new sf::Texture();
	if (!this->textures["bullet"]->loadFromFile("textures/bullet.png"))std::cout << "CANNOT LOAD BULLET TEXTURE.\n";

}



void Game::initplayer()
{
	this->p1 = new player();

	acc = 1.f;
	drag = 0.2;
	vel = sf::Vector2f(0.2f, 0.2f);
	maxVel = sf::Vector2f(10.f, 4.f);

	this->p1->setPos(sf::Vector2f(this->app->getSize().x / 2.f - this->p1->getBounds().width/2.f, this->app->getSize().y - this->p1->getBounds().height));
}

void Game::initEnemies()
{
	this->spawnTimerMax = 20;
	this->enemySpawnTimer = this->spawnTimerMax;
	this->enemySpawnPos = sf::Vector2f(this->app->getSize().x / 2, 0.f);
}



Game::Game()
{
	srand(time(NULL));

	this->initapp();
	this->initWorld();
	this->initTextures();
	this->initplayer();
	this->initEnemies();
	this->initGUI();
}



Game::~Game()
{
	delete this->app;
	delete this->p1;

	for (auto &ptr : this->textures)
	{
		delete ptr.second;
	}

	for (auto *i : this->bullets)
	{
		delete i;
	}
}



void Game::updatePollEvent()
{
	sf::Event e;
	while (this->app->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->app->close();
	}
}



void Game::updateBullet()
{
	unsigned int c{0};
	for (auto &bullet : this->bullets)
	{
		bullet->update();

		//BULLET DELETING WHEN HITS THE CEILING
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//DELETE THAT BULLET
			delete this->bullets.at(c);
			this->bullets.erase(this->bullets.begin() + c);
			c--;
		}
		c++;
	}

}

void Game::updateEnemies()
{
	if (this->enemySpawnTimer < this->spawnTimerMax)
		this->enemySpawnTimer += 1.5f;
	else
	{
		this->enemySpawnPos.x += rand() % 2000 - rand() % 2000;

		if (this->enemySpawnPos.x < 0.f)this->enemySpawnPos.x = 0.f;
		else if (this->enemySpawnPos.x > this->app->getSize().x - 25)this->enemySpawnPos.x = this->app->getSize().x - 25.f;

		this->enemies.push_back(new Enemy(sf::Vector2f(this->enemySpawnPos.x, -100.f), this->app->getSize().x - 600.f));
		this->enemySpawnTimer = 0.f;
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		this->enemies[i]->update();

		//BULLET AND ENEMY COLLISION
		for (int j = 0; j < bullets.size(); j++)
		{
			if (this->bullets[j]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->bullets.erase(this->bullets.begin() + j);
				this->enemies[i]->takeDamage(10);

				if (this->enemies[i]->getHP() == 0)
				{
					points += this->enemies[i]->getPoint();
					this->enemies.erase(this->enemies.begin() + i);
					return;
				}
			}
		}

		if (this->p1->getBounds().intersects(this->enemies[i]->getBounds()))
		{
			this->p1->takeDamage(this->enemies[i]->giveDamage());
			this->enemies.erase(this->enemies.begin() + i);
			return;
		}

		//REMOVE ENEMIES OUT OF BOUNDS
		if (this->enemies[i]->getBounds().top > app->getSize().y)
			this->enemies.erase(this->enemies.begin() + i);
	}
}

void Game::updateInput()
{
	//-----------------MOVE PLAYER-----------------
	//ACCELERATION

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && vel.x > -maxVel.x)
	{
		vel.x -= acc;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && vel.x < maxVel.x)
	{
		vel.x += acc;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && vel.y > -maxVel.y)
	{
		vel.y -= acc;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && vel.y < maxVel.y)
	{
		vel.y += acc;
	}
	//DRAG
	if (vel.x > 0)
	{
		vel.x -= drag;
		if (vel.x < 0)vel.x = 0;
	}
	else if (vel.x < 0)
	{
		vel.x += drag;
		if (vel.x > 0)vel.x = 0;
	}
	if (vel.y > 0)
	{
		vel.y -= drag;
		if (vel.y < 0)vel.y = 0;
	}
	else if (vel.y < 0)
	{
		vel.y += drag;
		if (vel.y > 0)vel.y = 0;
	}
	//MOVEMENT BY VELOCITY
	this->p1->move(vel.x, vel.y);

	//CREATING BULLET
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->p1->canAttack())
	{
		this->bullets.push_back(new bullet(*this->textures["bullet"], sf::Vector2f(this->p1->getpos().x + this->p1->getBounds().width / 2 - 15.f, this->p1->getpos().y), 0.f, -1.f, 10.f));
	}

}

void Game::updateGUI()
{
	//UPDATE POINTS GUI
	std::stringstream ss;
	ss << "POINTS:->" <<  this->points;
	this->text.setString(ss.str());

	//UPDATE PLAYER HEALTH BAR
	float hpPercent = static_cast<float>( this->p1->getHp() ) / this->p1->getMaxHp() ;
	this->hpBar.setSize(sf::Vector2f(450 * hpPercent, this->hpBar.getSize().y));

}

void Game::updateCollision()
{
	//-----------------------PLAYER IN BOUNDS CHECK---------------------------
	if (this->p1->getBounds().left < 0.f)p1->setPos(sf::Vector2f(0.f, this->p1->getBounds().top));
	else if (this->p1->getBounds().left > this->app->getSize().x-this->p1->getBounds().width)p1->setPos(sf::Vector2f(this->app->getSize().x - this->p1->getBounds().width, this->p1->getBounds().top));
	
	if (this->p1->getBounds().top < 0.f)p1->setPos(sf::Vector2f(this->p1->getBounds().left, 0.f));
	else if (this->p1->getBounds().top > this->app->getSize().y - this->p1->getBounds().height - 30.f)p1->setPos(sf::Vector2f(this->p1->getBounds().left, this->app->getSize().y - this->p1->getBounds().height - 30.f));
}


void Game::run()
{
	while (this->app->isOpen())
	{
		
		this->updatePollEvent();
		
		if (!isStart)
		{
			welcome();
		}
		else {
			if (this->p1->getHp() > 0)
				this->update();
			this->render();
		}
	}
}

void Game::update()
{
	//======================================UPDATE================================================
	this->updateInput();
	
	this->p1->update();
	this->updateCollision();

	this->updateBullet();

	this->updateEnemies();

	this->updateGUI();
}

void Game::renderGUI()
{
	this->app->draw(this->text);
	this->app->draw(this->hpBar);
	this->app->draw(this->maxHpBar);
}

void Game::renderWorld()
{
	this->app->draw(this->Bg);
}

void Game::render()
{
	this->app->clear();

	//=================================DRAW================================
	//DRAW WORLD
	this->renderWorld();

	//DRAW STUFF
	this->p1->render(*this->app);

	for (auto bullet : this->bullets)
	{
		bullet->render(this->app);
	}
	for (auto enemy : this->enemies)
	{
		enemy->render(this->app);
	}
	
	this->renderGUI();

	//GAME OVER TEXT
	if (this->p1->getHp() <= 0)
	{
		this->Bg.setColor(sf::Color::Color(255, 255, 255, 128));
		this->app->draw(this->gameOver);
		Restart();
	}

	this->app->display();
}

void Game::Restart()
{

	this->app->draw(this->restart);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{

		this->Bg.setColor(sf::Color::Color(255, 255, 255, 255));
		this->points = 0;
		this->p1->resetHp();
		this->p1->setPos(sf::Vector2f(this->app->getSize().x / 2.f - this->p1->getBounds().width / 2.f, this->app->getSize().y - this->p1->getBounds().height));
	}
}