#pragma once

#include "Graphics.h"
#include "Config.h"
#include "Sound.h"

class GeneralGame
{
public:
	GeneralGame();
	void GameWonBanner(Graphics& gfx) const;
	void GameLostBanner(Graphics& gfx) const;
	void DrawScore(Graphics& gfx) const;
	void DrawGameBorder(Graphics& gfx) const;
	bool GameOverStatus();
	int ScoreStatus();
	void StartGame();
	void GameOver();
	void GameWon();
	void AddScore();
	void GameOverDrawLogic(Graphics& gfx) const;
	void DrawGame(Graphics& gfx) const;
	void UpdateGame(float dt);
private:
	bool gameOver = true; 
	bool gameWon = true;
	int score = 0;
	int scoreX = Graphics::ScreenWidth / Config::maxScore;
	float frameCount;
	Sound startGame;
	Sound gameMusic;
	Surface lost = Surface("Images\\GameLost 400x200.bmp");
	Surface won = Surface("Images\\GameWon 400x200.bmp");
};