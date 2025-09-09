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
	gameMusic(L"Sounds\\5_gameMusic.wav", Sound::LoopType::AutoFullSound),
	count(0.0f)
{
	gameMusic.Play(1.0f, 0.4f);

	//Kamiza
	kamiza = std::make_unique<Kamiza>(Vec2(-60.0f,-60.0f));

	//Player
	player = std::make_unique<Player>(Vec2(xRand(rng), yRand(rng)));

	//Camera
	cam = std::make_unique<Camera>(player->GetCenter());

	//Enemy
	enemy.reserve(Config::enemyNum);
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
	for (Bullet& b : bul)
	{
		b.Update(*player, dt);
	}

	bul.erase(
		std::remove_if(bul.begin(), bul.end(),
			[](Bullet& b) { return b.SmashedStatus(); }),
		bul.end());

	
	//Enemy
	count += dt;
	if (count > Config::enemyRespawnTime && enemy.size() < n)
	{
		enemy.emplace_back(Vec2(xRand(rng), yRand(rng)));
		count = 0.0f;
	}
	// Update all enemies
	for (Enemy& e : enemy)
	{
		e.Update(*player, dt);

		// Handle collisions with player
		if (e.Colliding(*player) && !player->DestroyedStatus())
		{
			player->Damaged();
			playerDamaged.Play();
		}

		// Handle collisions with bullets
		for (Bullet& b : bul)
		{
			if (e.Colliding(b))
			{
				e.Damaged();
				b.Smashed();
			}
		}
	}
	// Remove destroyed enemies and spawn collectables
	enemy.erase(
		std::remove_if(enemy.begin(), enemy.end(),
			[&](Enemy& e)
			{
				if (e.DestroyedStatus())
				{
					coll.emplace_back(e.GetPos()); // spawn collectable
					objDamaged.Play();
					return true; // remove this enemy
				}
				return false; // keep enemy
			}),
		enemy.end());
	

	//Collectable
	coll.erase(
		std::remove_if(coll.begin(), coll.end(),
			[&](Collectable& c)
			{
				if (c.Colliding(*player))
				{
					objCollected.Play();
					return true;
				}
				return false;
			}),
		coll.end());


	//Camera
	cam->Follow(player->GetCenter());


	//Kamiza
	//Collectable
	//Player
	//Enemy
	//Bullet
	objects.clear(); 
	objects.reserve(1 + coll.size() + 1 + enemy.size() + bul.size());
	objects.push_back(kamiza.get());
	for (Collectable& c : coll) 
		objects.push_back(&c);
	objects.push_back(player.get());
	for (Enemy& e : enemy) 
		objects.push_back(&e);
	for (Bullet& b : bul) 
		objects.push_back(&b);
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
	//Kamiza
	//Collectable
	//Player
	//Enemy
	//Bullet
	for (GameObject* obj : objects)
	{
		obj->Draw(*cam, gfx);
	}

	//Latency
	bigFont.DrawText("Latency: " + std::to_string(latency) + "ms", {Graphics::ScreenWidth - 240, Graphics::ScreenHeight - 50}, Colors::Red, gfx);

	//WorldPosition
	smallFont.DrawText(std::to_string((int)worldPos.x) + ", " + std::to_string((int)worldPos.y), { Graphics::ScreenWidth - 240, 50 }, Colors::White, gfx);

	//Menu
	if (menu)
	{
		menu->Draw(gfx);
	}
}