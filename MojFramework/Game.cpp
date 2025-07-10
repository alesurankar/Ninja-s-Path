#include "Game.h"

Game::Game()
	:
	rng(rd()),
	xRand(0.0f, static_cast<float>(Graphics::ScreenWidth)),
	yRand(0.0f, static_cast<float>(Graphics::ScreenHeight)),
	fireSound(L"Sounds\\1_fireSound.wav"),
	objCollected(L"Sounds\\2_objcollected.wav"),
	objDamaged(L"Sounds\\3_objDamaged.wav"),
	playerDamaged(L"Sounds\\4_playerDamaged.wav"),
	gameMusic(L"Sounds\\5_gameMusic.wav", Sound::LoopType::AutoFullSound)
{
	gameMusic.Play(1.0f, 0.4f);
	//Kamiza
	kamiza = std::make_unique<Kamiza>(Vec2(880.0f, 20.0f));

	//Player
	player = std::make_unique<Player>(Vec2(xRand(rng), yRand(rng)));

	//Bullet
	bul.clear();
	
	//Enemy
	enemy.clear();
	count = 0.0f;
	
	//Collectable
	coll.clear();
}

void Game::UpdateGame(const Mouse& mouse, const Keyboard& kbd, float dt)
{
	//Menu
	if (!menu && kbd.KeyIsPressed(VK_ESCAPE))
	{
		CreateMenu();
	}
	if (menu)
	{
		menu->Update(mouse);
		std::string menuMessage = menu->GetMenuMessage();
		if (menuMessage == "Close")
		{
			DestroyMenu();
		}
		if (menuMessage == "Quit to Main Menu")
		{
			gameMessage = "Menu";
		}
		if (menuMessage == "Quit and Exit")
		{
			gameMessage = "Exit";
		}
	}

	//Latency
	const int refreshRate = 16;
	frameTimes.push_back(static_cast<int>(dt * 1000));
	if (frameTimes.size() > refreshRate)
	{
		frameTimes.pop_front();
	}
	if (frameTimes.size() == refreshRate)
	{
		int sum = std::accumulate(frameTimes.begin(), frameTimes.end(), 0);
		latency = static_cast<int>(sum / frameTimes.size());
	}

	//Player
	if (!menu)
	{
		player->Update(mouse, kbd, dt);
	}
	if (player->FiringStatus())
	{
		bul.emplace_back(player->GetCenter(), player->GetDirection(mouse));
		fireSound.Play();
	}

	if (player->Colliding(*kamiza))
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
		if (enemy[e].Colliding(*player) && !player->DestroyedStatus())
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
			}
		}
		if (enemy[e].DestroyedStatus())
		{
			coll.emplace_back(enemy[e].GetPos());
			enemy.erase(enemy.begin() + e);
			objDamaged.Play();
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
			coll.erase(coll.begin() + c);
			objCollected.Play();
		}
		else
		{
			c++;
		}
	}
}

void Game::CreateMenu()
{
	menu = std::make_unique<Menu>(Menu::MenuType::IN_GAME);
}

void Game::DestroyMenu()
{
	menu.reset();
}

std::string Game::GetGameMessage()
{
	return gameMessage;
}

void Game::DrawGame(Graphics& gfx)
{
	//kamiza
	kamiza->Draw(gfx);

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
	bigFont.DrawText("Latency: " + std::to_string(latency) + "ms", {Graphics::ScreenWidth - 240, Graphics::ScreenHeight - 50}, Colors::Red, gfx);

	//Menu
	if (menu)
	{
		menu->Draw(gfx);
	}
}