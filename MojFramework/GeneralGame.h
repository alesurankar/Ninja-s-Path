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
#include "Point.h"
#include "Player.h"

class GeneralGame
{
public:
	GeneralGame();
	void GameWonBanner(Graphics& gfx) const;
	void GameLostBanner(Graphics& gfx) const;
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
	std::vector<Enemy> enemy;
	std::vector<Point> point;
	std::vector<Bullet> bul;
	Sound fireSound;
	Sound objCollected;
	Sound enemyDestroyed;
	Sound playerDamaged;
	Sound gameMusic;
	float count;
	bool gameOver = true; 
	bool gameWon = true;
	Surface lost = Surface("Images\\GameLost 400x200.bmp");
	Surface won = Surface("Images\\GameWon 400x200.bmp");
public:
	int maxScore = 6;
	static constexpr int enemyNum = 20;
	static constexpr float enemyRespawnTime = 1.0f;
	int score = 0;
	int scoreX = Graphics::ScreenWidth / maxScore;
	static constexpr int n = enemyNum;
};