#pragma once

#include "Graphics.h"
#include "Config.h"

class GeneralGame
{
public:
	void GameWonBanner(Graphics& gfx) const;
	void GameLostBanner(Graphics& gfx) const;
	void DrawScore(Graphics& gfx) const;
	void DrawGameBorder(Graphics& gfx) const;
	bool GameOverStatus();
	bool GameWonStatus();
	int ScoreStatus();
	void StartGame();
	void GameOver();
	void GameWon();
	void AddScore();
private:
	bool gameOver = true; 
	bool gameWon = true;
	int score = 0;
	int scoreX = Graphics::ScreenWidth / Config::maxScore;
};