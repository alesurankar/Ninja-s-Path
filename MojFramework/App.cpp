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
	dt = ft.CheckTime();
	gfx.BeginFrame(Colors::DarkGray);
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
	DoFrameRate(frameRate, dt);
}

void App::UpdateModel()
{
	if (state == State::Menu)
	{
		frameRate = 0.032f;
		menu->Update(wnd.mouse);
		std::string message = menu->GetMenuMessage();
		if (message == "Exit")
		{
			wnd.Kill();
		}
		if (message == "Play now")
		{
			DestroyMenu();
			state = State::PlayGame;
			CreateGame();
		}
	}

	if (state == State::PlayGame)
	{
		frameRate = 0.016f;
		gg->UpdateGame(wnd.mouse, wnd.kbd, dt);
		std::string message = gg->GetGameMessage();
		if (message == "Exit")
		{
			wnd.Kill();
		}
		if (message == "Menu")
		{
			DestroyGame();
			state = State::Menu;
			CreateMenu();
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
		menu = new Menu(Menu::MenuType::MAIN);
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

void App::DoFrameRate(float frameRate_ms, float dt)
{
	float targetFrameRate = frameRate_ms * 2; //bad calculation temporary fix
	float sleepTime = targetFrameRate - dt;
	std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
}

void App::ComposeFrame()
{
	if (state == State::Menu)
	{
		menu->Draw(gfx);
	}

	if (state == State::PlayGame)
	{
		gg->DrawGame(gfx);
	}
}