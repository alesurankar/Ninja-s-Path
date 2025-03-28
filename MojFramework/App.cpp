#include "MainWindow.h"
#include "App.h"

App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{}

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

	if (state == State::GameOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			state = State::Menu;
		}
	}


	while (!wnd.mouse.IsEmpty())
	{
		const auto m = wnd.mouse.Read();
		if (state == State::Menu)
		{
			if (m.GetType() == Mouse::Event::Type::LPress)
			{
				gg.StartGame();
				state = State::PlayGame;
			}
		}
	}

	if (state == State::PlayGame)
	{
		gg.UpdateGame(wnd.mouse, wnd.kbd, dt);
		if (gg.GameOverStatus())
		{
			state = State::GameOver;
		}
	}
}

void App::ComposeFrame()
{
	if (state == State::GameOver)
	{
		gg.GameOverDrawLogic(gfx);
	}

	if (state == State::Menu)
	{
		menu.Draw(gfx);
	}

	if (state == State::PlayGame)
	{
		gg.DrawGame(gfx);
	}
}