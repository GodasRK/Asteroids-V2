#include "Game.h"
#include "Bullet.h"

int score = 10;

void Game::initText()
{
	this->text.setFont(font);
	this->text.setString("0");
	this->text.setCharacterSize(50);
	this->text.setFillColor(sf::Color::White);
	this->text.setPosition(700 / 2.0f, 10.f);
	this->font.loadFromFile("Textures/arialbd.ttf");
	
}

void Game::initWinodw()
{
	this->window = new RenderWindow(VideoMode(800, 600),"Asteroids", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures[ET_BULLET] = new Texture();
	this->textures[ET_BULLET]->loadFromFile("Textures/bullet.png");
}

void Game::initShip()
{
	this->ship = new Ship(350,500);
	this->hp = 1;
}

void Game::initAsteroids()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initWorld()
{
	this->worldBackgroundTex.loadFromFile("Textures/background.jpg");
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initGUI()
{
	this->gameOverText.setFont(font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 3.3,this->window->getSize().y / 2.5);
	
}




Game::Game()
{
	
	this->initWinodw();
	this->initTextures();
	this->initShip();
	this->initGUI();
	this->initAsteroids();
	this->initText();
	this->initWorld();
}

Game::~Game()
{
	delete this->window;
	delete this->ship;

	for (auto &i : this->textures)
	{
		delete i.second;
	}
	for (auto *i : this->bullets)
	{
		delete i;
	}
	for (auto* i : this->asteroids)
	{
		delete i;
	}

}



 void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		if (this->hp == 1)
		{
			score++;
			this->update();
		}
		
		
		this->render();
	}
	
}

void Game::updatePollEvents()
{
	Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == Event::Closed)
			this->window->close();
		
		
	}
}

void Game::updateInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::A))
		this->ship->move(-1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Key::Right) || Keyboard::isKeyPressed(Keyboard::Key::D))
		this->ship->move(1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Key::Up) || Keyboard::isKeyPressed(Keyboard::Key::W))
		this->ship->move(0.f, -1.f);
	if (Keyboard::isKeyPressed(Keyboard::Key::Down) || Keyboard::isKeyPressed(Keyboard::Key::S))
		this->ship->move(0.f, +1.f);
	if (Keyboard::isKeyPressed(Keyboard::Key::Space)&&this->ship->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures[ET_BULLET],this->ship->getPos().x+ this->ship->getBounds().width/20, this->ship->getPos().y, 0.f, -2.f, 5.f));
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();


		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{

			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}

}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	if (this->ship->getBounds().left < 0.f)
	{
		this->ship->setPosition(0.f, this->ship->getBounds().top);
	}
    else if (this->ship->getBounds().left+ this->ship->getBounds().width >= this->window->getSize().x)
	{
		this->ship->setPosition(this->window->getSize().x- this->ship->getBounds().width, this->ship->getBounds().top);
	}

	if (this->ship->getBounds().top < 0.f)
	{
		this->ship->setPosition(this->ship->getBounds().left,0.f);
	}
	else if (this->ship->getBounds().top + this->ship->getBounds().height >= this->window->getSize().y)
	{
		this->ship->setPosition(this->ship->getBounds().left, this->window->getSize().y - this->ship->getBounds().height);
	}
}

void Game::updateAsteroidsAndCombat()
{
	this->spawnTimer += 5.f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->asteroids.push_back(new Asteroid(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	for (int i = 0; i < this->asteroids.size(); i++)
	{
		bool enemy_removed = false;
		this->asteroids[i]->update();

		for (int k = 0; k < this->bullets.size() && !enemy_removed; k++)
		{
			if (this->bullets[k]->getBounds().intersects(this->asteroids[i]->getBounds()))
			{
				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);
				delete this->asteroids[i];
				this->asteroids.erase(this->asteroids.begin() + i);
				enemy_removed = true;
			}
		}
		if (!enemy_removed)
		{
			if (this->asteroids[i]->getBounds().top > this->window->getSize().y)
			{
				delete this->asteroids[i];
				this->asteroids.erase(this->asteroids.begin() + i);
				enemy_removed = true;

			}
			else if (asteroids[i]->getBounds().intersects(this->ship->getBounds()))
			{
				this->hp = 0;
				delete this->asteroids[i];
				this->asteroids.erase(this->asteroids.begin() + i);
				enemy_removed = true;
			}

		}
		

	}
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::renderGUI()
{
	
}

void Game::update()
{

	
	this->updateInput();
	this->ship->update();
	this->updateCollision();
	this->updateBullets();
	this->updateAsteroidsAndCombat();
	this->updateWorld();
}
	

void Game::render()
{
	

	this->window->clear();

	this->renderWorld();

	this->ship->render(*this->window);

	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	for (auto* asteroid : this->asteroids)
	{
		asteroid->render(this->window);
		
	}

	this->text.setString(to_string(score));
	window->draw(text);

	this->renderGUI();

	if (this->hp == 0)
		this->window->draw(this->gameOverText);
	
	this->window->display();
	
	
}
