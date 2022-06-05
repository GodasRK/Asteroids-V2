#include "Ship.h"



void Ship::initTexture()
{
	this->texture.loadFromFile("Textures/ship.png");
}

void Ship::initSprite()
{
	this->sprite.setTexture(this->texture);
}

void Ship::initVariables()
{
	this->speed = 5.f;
	this->coolMax = 10.f;
	this->cool = this->coolMax;
}

Ship::Ship(int pos_x, int pos_y)
{ 
	this->sprite.setPosition(pos_x, pos_y);
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Ship::~Ship()
{

}

const Vector2f& Ship::getPos() const
{
	return this->sprite.getPosition();
}

const FloatRect Ship::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Ship::updateCool()
{
	if(this->cool<this->coolMax)
	this->cool += 0.5f;
}

const bool Ship::canAttack()
{
	if (this->cool >= this->coolMax)
	{
		this->cool = 0.f;
		return true;
	}
		return false;
}

void Ship::update()
{
	this->updateCool();
}

void Ship::move(const float dirX, const float dirY)
{
	this->sprite.move(this->speed * dirX, this->speed * dirY);
}

void Ship::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
