#pragma once
#include <random>
#include <vector>
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
#include "Kamiza.h"
#include "Menu.h"
#include "Camera.h"
#include <deque>
#include <numeric>
#include <memory>

class Game
{
public:
	Game();
	void DrawGame(Graphics& gfx);
	void UpdateGame(const Mouse& mouse, const Keyboard& kbd, float dt);
	void CreateMenu();
	void DestroyMenu();
	std::string GetGameMessage();
private:
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> xRand;
	std::uniform_real_distribution<float> yRand;
	std::uniform_real_distribution<float> vRand;
	std::string gameMessage;
	std::unique_ptr<Player> player;
	std::unique_ptr<Menu> menu;
	static constexpr int n = Config::enemyNum;
	std::vector<Enemy> enemy;
	std::vector<Collectable> coll;
	std::vector<Bullet> bul;
	std::unique_ptr<Kamiza> kamiza;
	std::unique_ptr<Camera> cam;
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
	Vec2 worldPos;
};