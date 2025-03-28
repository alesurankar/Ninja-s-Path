#include "MainWindow.h"
#include "App.h"

App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	CreateMenu();
}

App::~App()
{
	DestroyGame();
	DestroyMenu();
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

	if (state == State::GameOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			DestroyGame();
			CreateMenu();
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
				DestroyMenu();
				CreateGame();
				gg->StartGame();
				state = State::PlayGame;
			}
		}
	}

	if (state == State::PlayGame)
	{
		gg->UpdateGame(wnd.mouse, wnd.kbd, dt);
		if (gg->GameOverStatus())
		{
			state = State::GameOver;
		}
	}
}

void App::CreateGame()
{
	if (gg == nullptr)
	{
		gg = new GeneralGame;
	}
}

void App::DestroyGame()
{
	if (gg != nullptr)
	{
		delete gg;
		gg = nullptr;
	}
}

void App::CreateMenu()
{
	if (menu == nullptr)
	{
		menu = new Menu;
	}
}

void App::DestroyMenu()
{
	if (menu != nullptr)
	{
		delete menu;
		menu = nullptr;
	}
}

void App::ComposeFrame()
{
	if (state == State::GameOver)
	{
		gg->GameOverDrawLogic(gfx);
	}

	if (state == State::Menu)
	{
		menu->Draw(gfx);
	}

	if (state == State::PlayGame)
	{
		gg->DrawGame(gfx);
	}
}