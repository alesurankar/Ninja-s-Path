#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Sound.h"
#include "Config.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Collectable.h"
#include "Player.h"
#include "Fonts.h"
#include "Altar.h"
#include <random>
#include <vector>
#include <deque>
#include <numeric>
#include "Menu.h"

#include "MapGrid.h"


struct DamagePopup
{
	int damage;
	Vei2 pos;
	float timeLeft = 0.2f;
};

class GeneralGame
{
public:
	GeneralGame();
	~GeneralGame();
	void DrawGame(Graphics& gfx);
	void UpdateGame(const Mouse& mouse, const Keyboard& kbd, float dt);
	void CreatePlayer();
	void DestroyPlayer();
	void CreateMenu();
	void DestroyMenu();
	std::string GetMessage();
private:
	std::string gameMessage;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> xRand;
	std::uniform_real_distribution<float> yRand;
	std::uniform_real_distribution<float> vRand;
	Player* player = nullptr;
	Menu* menu = nullptr;
	static constexpr int n = Config::enemyNum;
	std::vector<Enemy> enemy;
	std::vector<Collectable> coll;
	Altar altar;
	std::vector<Bullet> bul;
	Sound fireSound;
	Sound objCollected;
	Sound objDamaged;
	Sound playerDamaged;
	Sound gameMusic;
	float count;
	std::deque<int> frameTimes;
	int latency = 0;
	Fonts bigFont = Fonts("Images\\Fonts16x28.bmp");
	Fonts smallFont = Fonts("Images\\Fonts8x14.bmp"); 
	std::vector<DamagePopup> damagePopups;
	MapGrid mapGrid;
};