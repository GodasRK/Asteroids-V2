#ifndef BULLET_H
#define BULLET_H

#include<SFML/Graphics.hpp>
#include<iostream>

using namespace sf;
using namespace std;


class Bullet
{
private:

	Sprite shape;

	Vector2f direction;
	float movementSpeed;

public:
	Bullet();
	Bullet(Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	
	const FloatRect getBounds() const;

	void update();
	void render(RenderTarget* target);
};

#endif 

