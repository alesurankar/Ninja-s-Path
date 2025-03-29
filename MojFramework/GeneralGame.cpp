#include "GeneralGame.h"

GeneralGame::GeneralGame()
	:
	rng(rd()),
	xRand(20.0f, 770.0f),
	yRand(20.0f, 570.0f),
	fireSound(L"Sounds\\1_fireSound.wav"),
	objCollected(L"Sounds\\2_objcollected.wav"),
	objDamaged(L"Sounds\\3_objDamaged.wav"),
	playerDamaged(L"Sounds\\4_playerDamaged.wav"),
	startGame(L"Sounds\\5_startGame.wav"),
	gameMusic(L"Sounds\\6_gameMusic.wav")
{
	//Player
	CreatePlayer();

	//Bullet
	bul.clear();

	//Enemy
	enemy.clear();

	//Collectable
	point.clear();

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

void GeneralGame::DrawGameBorder(Graphics& gfx) const
{

	gfx.DrawRect(0, 2 * Config::offset + Config::scoreY, Config::offset, Graphics::ScreenHeight, Colors::Blue);
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
	//Player
	player->Update(mouse, kbd, dt);
	if (player->FiringStatus())
	{
		bul.emplace_back(player->GetCenter(), player->GetDirection(mouse));
		fireSound.Play();
	}

	if (player->DestroyedStatus())
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
	if (count > enemyRespawnTime && enemy.size() < n)
	{
		enemy.emplace_back(Vec2(xRand(rng), yRand(rng)), Vec2(vRand(rng), vRand(rng)));
		count = 0.0f;
	}

	for (int e = 0; e < enemy.size();)
	{
		enemy[e].Update(dt);
		if (enemy[e].Colliding(*player))
		{
			player->TakeDamage(enemy[e], enemy[e].MeleDamage());
			playerDamaged.Play();
			enemy[e].TakeDamage(*player, player->MeleDamage());
			objDamaged.Play();
		}
		for (Bullet& b : bul)
		{
			if (enemy[e].Colliding(b))
			{
				enemy[e].TakeDamage(*player, b.DamageBonus());
				b.Smashed();
				objDamaged.Play();
			}
		}
		if (enemy[e].DestroyedStatus())
		{
			point.emplace_back(enemy[e].GetPos());
			enemy.erase(enemy.begin() + e);
		}
		else
		{
			e++;
		}
	}

	//Collectable
	for (int p = 0; p < point.size();)
	{
		if (point[p].Colliding(*player))
		{
			score++;
			point.erase(point.begin() + p);
			if (score >= maxScore)
			{
				gameOver = true;
				gameWon = true;
			}
			objCollected.Play();
		}
		else
		{
			p++;
		}
	}

	//GeneralGame
	if (GameOverStatus())
	{
		DestroyPlayer();
		gameMusic.StopAll();
	}
	frameCount += dt;
	if (frameCount > 3.4f)
	{
		gameMusic.Play();
		frameCount = 0.0f;
	}
}

void GeneralGame::CreatePlayer()
{
	if (player == nullptr)
	{
		player = new Player(Vec2(xRand(rng), yRand(rng)));
	}
}

void GeneralGame::DestroyPlayer()
{
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
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
	//Player
	player->Draw(gfx);

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
	for (Point& p : point)
	{
		p.Draw(gfx);
	}

	//GeneralGame
	player->ShowHP(gfx);
	DrawGameBorder(gfx);
}