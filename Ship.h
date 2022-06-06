#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


using namespace sf;



class Ship
{
private:
	Sprite sprite;
	Texture texture;

	float speed;

	float cool;
		float coolMax;

	void initTexture();
	void initSprite();
	void initVariables();

public:

	Ship(int pos_x,int pos_y);
    virtual ~Ship();
	const Vector2f& getPos() const;
	const FloatRect getBounds() const;

	void setPosition(const Vector2f pos);
	void setPosition(const float x, const float y);

	void updateCool();
	const bool canAttack();
	void update();
	void move(const float dirX, const float dirY );

	void render(RenderTarget& target);

};

