#pragma once

#include "Graphics.h"

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
	int scoreX = Graphics::ScreenWidth / maxScore;
public:
	static constexpr int offset = 2;
	static constexpr int scoreY = 12;
	static constexpr int yOffset = 3 * offset + scoreY;
public:
	static constexpr int maxScore = 8;
	static constexpr float difficulty = 100.0f;
	static constexpr int enemyNum = 20;
	static constexpr float mySpeed = 100.0f;
	static constexpr float bulSpeed = 500.0f;
	static constexpr float bulDim = 6.0f;
	static constexpr int myLives = 100;
	static constexpr int enemyLives = 3;
};