#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Enemy.h"
#include "Collectable.h"
#include "Jaz.h"
#include "GeneralGame.h"
#include "Config.h"
#include "Bullet.h"
#include <random>
#include "FrameTimer.h"
#include "Sound.h"
#include <vector>

class App
{
public:
	App(class MainWindow& wnd);
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  Moije Funkcije              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  Moji Parametri              */
	FrameTimer ft;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> xRand;
	std::uniform_real_distribution<float> yRand;
	std::uniform_real_distribution<float> vRand;
	Jaz jaz;
	static constexpr int n = Config::enemyNum;
	std::vector<Enemy> enemy;
	Collectable coll;
	GeneralGame gg;
	std::vector<Bullet> bul;
	Sound fireSound;
	Sound objCollected;
	Sound objDamaged;
	Sound jazDamaged;
	Sound startGame;
	Sound gameMusic;
	float frameCount;
	/********************************/
};