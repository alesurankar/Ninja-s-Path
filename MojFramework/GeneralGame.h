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

class GeneralGame
{
public:
	GeneralGame();
	~GeneralGame();
	void GameWonBanner(Graphics& gfx) const;
	void GameLostBanner(Graphics& gfx) const;
	void DrawScore(Graphics& gfx) const;
	void DrawGameBorder(Graphics& gfx) const;
	bool GameOverStatus();
	void GameOverDrawLogic(Graphics& gfx) const;
	void DrawGame(Graphics& gfx);
	void UpdateGame(const Mouse& mouse, const Keyboard& kbd, float dt);
	void CreatePlayer();
	void DestroyPlayer();
private:
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> xRand;
	std::uniform_real_distribution<float> yRand;
	std::uniform_real_distribution<float> vRand;
	Player* player = nullptr;
	static constexpr int n = Config::enemyNum;
	//std::vector<Enemy> enemy;
	//std::vector<Collectable> coll;
	//std::vector<Bullet> bul;
	Sound fireSound;
	Sound objCollected;
	Sound objDamaged;
	Sound playerDamaged;
	Sound gameMusic;
	float count;
	bool gameOver = true; 
	bool gameWon = true;
	int score = 0;
	int scoreX = Graphics::ScreenWidth / Config::maxScore;
	Surface lost = Surface("Images\\GameLost 400x200.bmp");
	Surface won = Surface("Images\\GameWon 400x200.bmp");
};