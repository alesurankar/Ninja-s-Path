#include "GeneralGame.h"

GeneralGame::GeneralGame()
	:
	startGame(L"Sounds\\5_startGame.wav"),
	gameMusic(L"Sounds\\6_gameMusic.wav")
{
}

void GeneralGame::GameWonBanner(Graphics& gfx) const
{
	gfx.DrawRect(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Green);
}

void GeneralGame::GameLostBanner(Graphics& gfx) const
{
	gfx.DrawRect(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Red);
}

void GeneralGame::DrawScore(Graphics& gfx) const
{
	gfx.DrawRect(Config::offset, Config::offset,scoreX * score, Config::scoreY,Colors::Blue);
}

void GeneralGame::DrawGameBorder(Graphics& gfx) const
{
	gfx.DrawRect(0, 2* Config::offset + Config::scoreY, Config::offset, Graphics::ScreenHeight, Colors::Blue);
	gfx.DrawRect(0, Graphics::ScreenHeight - Config::offset, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Blue);
	gfx.DrawRect(Graphics::ScreenWidth - Config::offset, 2 * Config::offset + Config::scoreY, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Blue);
	gfx.DrawRect(0, 2 * Config::offset + Config::scoreY, Graphics::ScreenWidth, Config::yOffset, Colors::Blue);
}

bool GeneralGame::GameOverStatus()
{
	return gameOver;
}

int GeneralGame::ScoreStatus()
{
	return score;
}

void GeneralGame::StartGame()
{
	score = 0;
	gameOver = false;
	gameWon = false;
	frameCount = 1.3f;
	startGame.Play();
}

void GeneralGame::GameOver()
{
	gameOver = true;
}

void GeneralGame::GameWon()
{
	gameWon = true;
}

void GeneralGame::AddScore()
{
	score++;
}

void GeneralGame::GameOverDrawLogic(Graphics& gfx) const
{
	if (gameWon)
	{
		GameWonBanner(gfx);
	}
	else
	{
		GameLostBanner(gfx);
	}
}

void GeneralGame::DrawGame(Graphics& gfx) const
{
	DrawScore(gfx);
	DrawGameBorder(gfx);
}

void GeneralGame::UpdateGame(float dt)
{
	if (GameOverStatus())
	{
		gameMusic.StopAll();
	}
	frameCount += dt;
	if (frameCount > 3.4f)
	{
		gameMusic.Play();
		frameCount = 0.0f;
	}
}
