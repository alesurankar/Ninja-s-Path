#include "Game.h"

Game::Game()
	:
	rng(rd()),
	xRand(-static_cast<float>(Graphics::ScreenWidth), static_cast<float>(Graphics::ScreenWidth)),
	yRand(-static_cast<float>(Graphics::ScreenHeight), static_cast<float>(Graphics::ScreenHeight)),
	fireSound(L"Sounds\\1_fireSound.wav"),
	objCollected(L"Sounds\\2_objcollected.wav"),
	objDamaged(L"Sounds\\3_objDamaged.wav"),
	playerDamaged(L"Sounds\\4_playerDamaged.wav"),
	gameMusic(L"Sounds\\5_gameMusic.wav", Sound::LoopType::AutoFullSound)
{
	gameMusic.Play(1.0f, 0.4f);
	//Kamiza
	kamiza = std::make_unique<Kamiza>(Vec2(-60.0f,-60.0f));

	//Player
	player = std::make_unique<Player>(Vec2(xRand(rng), yRand(rng)));

	//Camera
	cam = std::make_unique<Camera>(player->GetCenter());

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
		worldPos = player->GetCenter();
	}
	if (player->FiringStatus())
	{
		bul.emplace_back(player->GetCenter(), player->GetDirection(*cam, mouse));
		fireSound.Play();
	}

	if (player->Colliding(*kamiza))
	{
		player->ActiveRegenerate(dt);
	}

	if (player->DestroyedStatus())
	{
		player->SetPos(kamiza->GetCenter());
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
			playerDamaged.Play();
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

	//Camera
	cam->Follow(player->GetCenter());
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
	kamiza->Draw(*cam, gfx);

	//Collectable
	for (Collectable& c : coll)
	{
		c.Draw(*cam, gfx);
	}
	
	//Bullet
	for (Bullet& b : bul)
	{
		if (!b.SmashedStatus())
		{
			b.Draw(*cam, gfx);
		}
	}
	
	//Enemy
	for (Enemy& e : enemy)
	{
		if (!e.DestroyedStatus())
		{
			e.Draw(*cam, gfx);
		}
	}

	//Player
	player->Draw(*cam, gfx);
	player->DrawStatus(gfx);
	player->DrawXP(gfx);

	//Latency
	bigFont.DrawText("Latency: " + std::to_string(latency) + "ms", {Graphics::ScreenWidth - 240, Graphics::ScreenHeight - 50}, Colors::Red, gfx);

	//WorldPosition
	smallFont.DrawText(std::to_string((int)worldPos.x) + ", " + std::to_string((int)worldPos.y), { Graphics::ScreenWidth - 240, 50 }, Colors::White, gfx);

	//Damage Popups
	for (DamagePopup popup : damagePopups)
	{
		popup.Draw(*cam, gfx);
	}

	//Menu
	if (menu)
	{
		menu->Draw(gfx);
	}
}