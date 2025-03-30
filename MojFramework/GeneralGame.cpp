#include "GeneralGame.h"

GeneralGame::GeneralGame()
	:
	rng(rd()),
	xRand(20.0f, 770.0f),
	yRand(20.0f, 570.0f),
	fireSound(L"Sounds\\1_fireSound.wav"),
	objCollected(L"Sounds\\2_objcollected.wav"),
	enemyDestroyed(L"Sounds\\3_enemyDestroyed.wav"),
	playerDamaged(L"Sounds\\4_playerDamaged.wav"),
	gameMusic(L"Sounds\\5_gameMusic.wav", Sound::LoopType::AutoFullSound)
{
	gameMusic.Play(1.0f, 0.3f);
	//Player
	CreatePlayer();

	//Bullet
	bul.clear();

	//Enemy
	enemy.clear();

	//Collectable
	point.clear();

	//GeneralGame
	gameOver = false;
	gameWon = false;
	count = 0.0f;
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

	gfx.DrawRect(0, 40, 2, Graphics::ScreenHeight, Colors::Blue);
	gfx.DrawRect(0, Graphics::ScreenHeight - 2, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Blue);
	gfx.DrawRect(Graphics::ScreenWidth -2 , 40, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Blue);
	gfx.DrawRect(0, 40, Graphics::ScreenWidth, 42, Colors::Blue);
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
		}
		for (Bullet& b : bul)
		{
			if (enemy[e].Colliding(b))
			{
				enemy[e].TakeDamage(*player, b.DamageBonus());
				b.Smashed();
			}
		}
		if (enemy[e].DestroyedStatus())
		{
			point.emplace_back(enemy[e].GetPos());
			enemy.erase(enemy.begin() + e);
			enemyDestroyed.Play();
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
			player->CollectXP();
			point.erase(point.begin() + p);
			if (player->CheckXP() >= 1000.0f)
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
	player->DrawStats(gfx);

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
	DrawGameBorder(gfx);
}