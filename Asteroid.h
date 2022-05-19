#ifndef ASTEROID_H
#define ASTEROID_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Asteroid
{
private:
	Sprite sprite;
	Texture texture;
	float speed;
	void initTexture();
	void initSprite();
	void initVariables();

public:
	Asteroid(float pos_x,float pos_y);
	virtual ~Asteroid();
	const FloatRect getBounds() const;


	void update();
	void render(RenderTarget* target);
};

#endif 
