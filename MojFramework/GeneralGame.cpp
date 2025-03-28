#include "GeneralGame.h"

GeneralGame::GeneralGame()
	:
	rng(rd()),
	xRand(20.0f, 770.0f),
	yRand(20.0f, 570.0f),
	vRand(-Config::difficulty, Config::difficulty),
	jaz(Vec2(xRand(rng), yRand(rng))),
	fireSound(L"Sounds\\1_fireSound.wav"),
	objCollected(L"Sounds\\2_objcollected.wav"),
	objDamaged(L"Sounds\\3_objDamaged.wav"),
	jazDamaged(L"Sounds\\4_jazDamaged.wav"),
	startGame(L"Sounds\\5_startGame.wav"),
	gameMusic(L"Sounds\\6_gameMusic.wav")
{
	//Jaz
	jaz.Respawn();

	//Bullet
	bul.clear();

	//Enemy
	enemy.clear();

	//Collectable
	coll.clear();

	//GeneralGame
	score = 0;
	gameOver = false;
	gameWon = false;
	frameCount = 1.3f;
	count = 0.0f;
	startGame.Play();
}

void GeneralGame::GameWonBanner(Graphics& gfx) const
{
	gfx.DrawRect(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Green);
	gfx.DrawImage(200, 200, won);
}

void GeneralGame::GameLostBanner(Graphics& gfx) const
{
	gfx.DrawRect(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Red);
	gfx.DrawImage(200, 200, lost);
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

void GeneralGame::UpdateGame(const Mouse& mouse, const Keyboard& kbd, float dt)
{
	//Jaz
	jaz.Update(mouse, kbd, dt);
	if (jaz.FiringStatus())
	{
		bul.emplace_back(jaz.GetCenter(), jaz.GetDirection(mouse));
		fireSound.Play();
	}

	if (jaz.DestroyedStatus())
	{
		gameOver = true;
	}

	//Bullet
	for (int b = 0; b < bul.size(); )
	{
		bul[b].Update(dt);
		if (bul[b].SmashedStatus())
		{
			bul.erase(bul.begin() + b);
		}
		else
		{
			b++;
		}
	}

	//Enemy
	count += dt;
	if (count > Config::enemyRespawnTime && enemy.size() < n)
	{
		enemy.emplace_back(Vec2(xRand(rng), yRand(rng)), Vec2(vRand(rng), vRand(rng)));
		count = 0.0f;
	}

	for (int e = 0; e < enemy.size();)
	{
		enemy[e].Update(dt);
		if (enemy[e].Colliding(jaz))
		{
			jaz.Damaged();
			jazDamaged.Play();
		}
		for (Bullet& b : bul)
		{
			if (enemy[e].Colliding(b))
			{
				enemy[e].Damaged();
				b.Smashed();
				objDamaged.Play();
			}
		}
		if (enemy[e].DestroyedStatus())
		{
			coll.emplace_back(enemy[e].GetPos());
			enemy.erase(enemy.begin() + e);
		}
		else
		{
			e++;
		}
	}

	//Collectable
	for (int c = 0; c < coll.size();)
	{
		if (coll[c].Colliding(jaz))
		{
			score++;
			coll.erase(coll.begin() + c);
			if (score >= Config::maxScore)
			{
				gameOver = true;
				gameWon = true;
			}
			objCollected.Play();
		}
		else
		{
			c++;
		}
	}

	//GeneralGame
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

void GeneralGame::DrawGame(Graphics& gfx)
{
	//Jaz
	jaz.Draw(gfx);

	//Bullet
	for (Bullet& b : bul)
	{
		if (!b.SmashedStatus())
		{
			b.Draw(gfx);
		}
	}

	//Enemy
	for (Enemy& e : enemy)
	{
		if (!e.DestroyedStatus())
		{
			e.Draw(gfx);
		}
	}

	//Collectable
	for (Collectable& c : coll)
	{
		c.Draw(gfx);
	}

	//GeneralGame
	DrawScore(gfx);
	DrawGameBorder(gfx);
}