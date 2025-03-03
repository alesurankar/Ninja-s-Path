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

			//Object
			for (int i = 0; i < n; i++)
			{
				objRed[i].Respawn();
				objRed[i].InitRed(Vec2(xRand(rng),yRand(rng)),Vec2(vRand(rng),vRand(rng)));
			}
			objBlue.InitBlue(Vec2(xRand(rng), yRand(rng)));

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
			if (!bul.FlyingStatus())
			{
				bul.Init(jaz.GetCenter(), jaz.GetDirection(wnd.mouse));
				bul.Flying();
				fireSound.Play();
			}
		}
		if (jaz.DestroyedStatus())
		{
			gg.GameOver();
		}

		//Bullet
		if (bul.FlyingStatus())
		{
			bul.Update(dt);
		}

		//Object
		for (int i = 0; i < n; i++)
		{
			objRed[i].Update(dt); 
			if (objRed[i].Colliding(jaz))
			{
				jaz.Damaged();
				jazDamaged.Play();
			}
			if (objRed[i].Colliding(bul))
			{
				objRed[i].Damaged();
				bul.Smashed();
				objDamaged.Play();
			}
		}
		if (objBlue.Colliding(jaz))
		{
			gg.AddScore();
			objBlue.InitBlue(Vec2(xRand(rng), yRand(rng)));
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
		if (bul.FlyingStatus())
		{
			bul.Draw(gfx);
		}

		//Object
		for (int i = 0; i < n; i++)
		{
			if (!objRed[i].DestroyedStatus())
			{
				objRed[i].DrawRed(gfx);
			}
		}
		objBlue.DrawBlue(gfx);
		
		//GeneralGame
		gg.DrawScore(gfx);
		gg.DrawGameBorder(gfx);
	}
}