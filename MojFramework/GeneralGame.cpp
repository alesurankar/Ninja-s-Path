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
	gameMusic(L"Sounds\\5_gameMusic.wav", Sound::LoopType::AutoFullSound),
	altar(Vec2(680.0f,10.0f)),
	mapGrid(5,4)
{
	gameMusic.Play(1.0f, 0.4f);
	//Player
	CreatePlayer();

	//Bullet
	bul.clear();
	
	//Enemy
	enemy.clear();
	count = 0.0f;
	
	//Collectable
	coll.clear();
}

GeneralGame::~GeneralGame()
{
	//player->SaveToFile("Config\\player_config.txt");
	DestroyPlayer();
}

void GeneralGame::UpdateGame(const Mouse& mouse, const Keyboard& kbd, float dt)
{
	//Latency
	frameTimes.push_back(static_cast<int>(dt * 1000));
	if (frameTimes.size() > 16)
	{
		frameTimes.pop_front();
	}

	if (frameTimes.size() == 16)
	{
		int sum = std::accumulate(frameTimes.begin(), frameTimes.end(), 0);
		latency = static_cast<int>(sum / frameTimes.size());
	}

	//Player
	player->Update(mouse, kbd, dt);
	if (player->FiringStatus())
	{
		bul.emplace_back(player->GetCenter(), player->GetDirection(mouse));
		fireSound.Play();
	}
	if (player->Colliding(altar))
	{
		player->ActiveRegenerate(dt);
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
		if (enemy[e].Colliding(*player) && !player->DestroyedStatus() && enemy[e].GetHitColldown() <= 1.0f)
		{
			int damage = player->TakeDamage(enemy[e], enemy[e].MeleDamage());
			Vei2 pos = Vei2(player->GetPos());
			damagePopups.push_back({ damage, pos });
			enemy[e].ResetHitCooldown();
		}
		for (Bullet& b : bul)
		{
			if (enemy[e].Colliding(b))
			{
				int damage = enemy[e].TakeDamage(*player, b.DamageBonus());
				Vei2 pos = Vei2(enemy[e].GetPos());
				damagePopups.push_back({ damage, pos });

				b.Smashed();
			}
		}
		if (enemy[e].DestroyedStatus())
		{
			coll.emplace_back(enemy[e].GetPos());
			enemy.erase(enemy.begin() + e); 
			player->CollectXP(enemy[e]);
			objDamaged.Play();
		}
		else
		{
			e++;
		}
	}
	
	//Damage Popups
	for (int i = 0; i < damagePopups.size(); )
	{
		damagePopups[i].timeLeft -= dt;
		if (damagePopups[i].timeLeft <= 0.0f)
			damagePopups.erase(damagePopups.begin() + i);
		else
			++i;
	}

	//Collectable
	for (int c = 0; c < coll.size();)
	{
		if (coll[c].Colliding(*player))
		{
			coll.erase(coll.begin() + c);
			objCollected.Play();
		}
		else
		{
			c++;
		}
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


void GeneralGame::DrawGame(Graphics& gfx)
{
	//mapGrid.Draw(gfx);
	

	//Altar
	altar.Draw(gfx);

	//Collectable
	for (Collectable& c : coll)
	{
		c.Draw(gfx);
	}
	
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
			e.DrawStatus(gfx);
		}
	}

	//Player
	player->Draw(gfx);
	player->DrawStatus(gfx);
	player->DrawXP(gfx);

	//Latency
	bigFont.DrawText("Latency: " + std::to_string(latency) + "ms", {550, 550}, Colors::Red, gfx);

	//Damage Popups
	for (const DamagePopup& popup : damagePopups)
	{
		bigFont.DrawText(std::to_string(popup.damage), popup.pos, Colors::Red, gfx);
	}
}