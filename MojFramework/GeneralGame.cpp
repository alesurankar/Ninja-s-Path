#include "GeneralGame.h"

GeneralGame::GeneralGame()
	:
	rng(rd()),
	xRand(20.0f, 740.0f),
	yRand(20.0f, 540.0f),
	fireSound(L"Sounds\\1_fireSound.wav"),
	objCollected(L"Sounds\\2_objcollected.wav"),
	objDamaged(L"Sounds\\3_objDamaged.wav"),
	playerDamaged(L"Sounds\\4_playerDamaged.wav"),
	gameMusic(L"Sounds\\5_gameMusic.wav", Sound::LoopType::AutoFullSound)
{
	gameMusic.Play(1.0f, 0.4f);
	//Player
	CreatePlayer();

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
	count = 0.0f;
}

GeneralGame::~GeneralGame()
{
	//player->SaveToFile("Config\\player_config.txt");
	DestroyPlayer();
}

void GeneralGame::GameWonBanner(Graphics& gfx) const
{
	RectI rect(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight);
	gfx.DrawRect(rect, Colors::Green);
	gfx.DrawImage(200, 200, won);
}

void GeneralGame::GameLostBanner(Graphics& gfx) const
{
	RectI rect(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight);
	gfx.DrawRect(rect, Colors::Red);
	gfx.DrawImage(200, 200, lost);
}

void GeneralGame::DrawScore(Graphics& gfx) const
{
	RectI rect(Config::offset, Config::offset, scoreX * score, Config::scoreY);
	gfx.DrawRect(rect,Colors::Blue);
}

void GeneralGame::DrawGameBorder(Graphics& gfx) const
{
	RectI rect(0, 2 * Config::offset + Config::scoreY, Graphics::ScreenWidth, Config::yOffset);
	gfx.DrawRect(rect, Colors::Blue);
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
		bul[b].Update(*player, dt);
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
		enemy.emplace_back(Vec2(xRand(rng), yRand(rng))); 
		count = 0.0f;
	}
	
	for (int e = 0; e < enemy.size();)
	{
		enemy[e].Update(*player, dt);
		if (enemy[e].Colliding(*player))
		{
			player->Damaged();
			playerDamaged.Play();
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
		if (coll[c].Colliding(*player))
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
		DestroyPlayer();
		gameMusic.StopAll();
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
	for (Collectable& c : coll)
	{
		c.Draw(gfx);
	}

	//GeneralGame
	DrawScore(gfx);
	DrawGameBorder(gfx);

	//Player
	player->DrawHOD(gfx);
}