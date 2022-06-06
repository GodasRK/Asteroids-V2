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

	Texture worldBackgroundTex;
	Sprite worldBackground;

	Text text;

	int hp;

	Text gameOverText;

	enum ETexture { ET_BULLET, green, blue };

	map<ETexture,Texture*> textures;
	vector <Bullet*> bullets;

	void initText();
	void initWinodw();
	void initTextures();
	void initShip();
	void initAsteroids();
	void initWorld();
	void initGUI();

public:

	Game();

	virtual ~Game();

	void run();

	void updatePollEvents();

	void updateInput();
	void updateBullets();
	void updateWorld();
	void updateCollision();
	void updateAsteroidsAndCombat();
	void renderWorld();
	void renderGUI();
	void update();

	void render();
};

