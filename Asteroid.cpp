#include "Asteroid.h"


void Asteroid::initTexture()
{
	this->texture.loadFromFile("Textures/Asteroid.png");
}
void Asteroid::initSprite()
{
	this->sprite.setTexture(this->texture);
}

void Asteroid::initVariables()
{
	this->speed = static_cast<float>(this->startingSpeed);
}


Asteroid::Asteroid(float pos_x, float pos_y)
{
	this->sprite.setPosition(pos_x, pos_y);
	this->initTexture();
	this->initSprite();

	this->initVariables();
}

Asteroid::~Asteroid()
{

}

const FloatRect Asteroid::getBounds() const
{
	return this->sprite.getGlobalBounds();
}


void Asteroid::update()
{
	this->sprite.move(0.f, this->speed);
}

void Asteroid::render(RenderTarget* target)
{
	target->draw(this->sprite);
}
