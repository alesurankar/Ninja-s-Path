#include "MainWindow.h"
#include "App.h"

App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd), 
	rng(rd()),
	xRand(20.0f, 770.0f),
	yRand(20.0f, 570.0f),
	vRand(-Config::difficulty, Config::difficulty),
	jaz(Vec2(xRand(rng),yRand(rng))),
	fireSound(L"Sounds\\1_fireSound.wav"),
	objCollected(L"Sounds\\2_objcollected.wav"),
	objDamaged(L"Sounds\\3_objDamaged.wav"),
	jazDamaged(L"Sounds\\4_jazDamaged.wav")
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
				enemy.erase(enemy.begin() + e);
			}
			else
			{
				e++;
			}
		}

		//Collectable
		if (coll.Colliding(jaz))
		{
			gg.AddScore();
			coll.Init(Vec2(xRand(rng), yRand(rng)));
			if (gg.ScoreStatus() >= Config::maxScore)
			{
				gg.GameOver();
				gg.GameWon();
			}
			objCollected.Play();
		}

		//GeneralGame
		gg.UpdateGame(dt);
	}
}

void App::ComposeFrame()
{
	if (gg.GameOverStatus())
	{
		gg.GameOverDrawLogic(gfx);
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
		gg.DrawGame(gfx);
	}
}