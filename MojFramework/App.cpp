#include "MainWindow.h"
#include "App.h"

App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd), 
	rng(rd()),
	xRand(20.0f, 770.0f),
	yRand(20.0f, 570.0f),
	vRand(-GeneralGame::difficulty, GeneralGame::difficulty),
	jaz(Vec2(xRand(rng),yRand(rng))),
	fireSound(L"Sounds\\1_fireSound.wav"),
	objCollected(L"Sounds\\2_objcollected.wav"),
	objDamaged(L"Sounds\\3_objDamaged.wav"),
	jazDamaged(L"Sounds\\4_jazDamaged.wav"),
	startGame(L"Sounds\\5_startGame.wav"),
	gameMusic(L"Sounds\\6_gameMusic.wav")
{
}

void App::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void App::UpdateModel()
{
	float dt = ft.CheckPoint();
	if (gg.GameOverStatus())
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			//Jaz
			jaz.Respawn();

			//Bullet
			bul.clear();

			//Enemy
			enemy.clear();
			for (int e = 0; e < n; e++)
			{
				enemy.emplace_back(Vec2(xRand(rng),yRand(rng)),Vec2(vRand(rng),vRand(rng)));
			}

			//Collectable
			coll.Init(Vec2(xRand(rng), yRand(rng)));

			//GeneralGame
			gg.StartGame();
			frameCount = 1.3f;
			startGame.Play();
		}
	}
	else
	{
		//Jaz
		jaz.Update(wnd.mouse, wnd.kbd, dt);
		if (jaz.FiringStatus())
		{
			bul.emplace_back(jaz.GetCenter(), jaz.GetDirection(wnd.mouse));
			fireSound.Play();
		}

		if (jaz.DestroyedStatus())
		{
			gg.GameOver();
		}

		//Bullet
		for (int b = 0; b < bul.size(); )
		{
			if (!bul[b].SmashedStatus())
			{
				bul[b].Update(dt);
				b++;
			}
			else
			{
				bul.erase(bul.begin() + b);
			}
		}

		//Enemy
		for (int e = 0; e < enemy.size();)
		{
			if (!enemy[e].DestroyedStatus())
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
				e++;
			}
			else
			{
				enemy.erase(enemy.begin() + e);
			}
		}

		//Collectable
		if (coll.Colliding(jaz))
		{
			gg.AddScore();
			coll.Init(Vec2(xRand(rng), yRand(rng)));
			if (gg.ScoreStatus() >= GeneralGame::maxScore)
			{
				gg.GameOver();
				gg.GameWon();
			}
			objCollected.Play();
		}

		//GeneralGame
		if (gg.GameOverStatus())
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
}

void App::ComposeFrame()
{
	if (gg.GameOverStatus())
	{
		if (gg.GameWonStatus())
		{
			gg.GameWonBanner(gfx);
		}
		else
		{
			gg.GameLostBanner(gfx);
		}
	}
	else
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
		coll.Draw(gfx);
		
		//GeneralGame
		gg.DrawScore(gfx);
		gg.DrawGameBorder(gfx);
	}
}