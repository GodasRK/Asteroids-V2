#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Ship.h"
#include <map>
#include "Bullet.h"
#include "Asteroid.h"

using namespace sf;
using namespace std;

class Game
{
private:
	Ship* ship;
	float spawnTimer;
	float spawnTimerMax;
	vector<Asteroid*> asteroids;
	
	RenderWindow* window;
	Font font;

	Text text;

	

	map<string,Texture*> textures;
	vector <Bullet*> bullets;

	void initText();
	void initWinodw();
	void initTextures();
	void initShip();
	void initAsteroids();

public:

	Game();

	virtual ~Game();

	void run();

	void updatePollEvents();

	void updateInput();
	void updateBullets();
	void updateAsteroidsAndCombat();

	void update();

	void render();
};

