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
	gfx.BeginFrame(Colors::DarkGray);
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame(delay);
}

void App::UpdateModel()
{
	float dt = ft.CheckTime();
	if (state == State::MENU)
	{
		delay = 3;
		menu->Update(wnd.mouse);
		std::string message = menu->GetMenuMessage();
		if (message == "Exit")
		{
			wnd.Kill();
		}
		if (message == "Play now")
		{
			DestroyMenu();
			state = State::GAME;
			CreateGame();
		}
	}

	if (state == State::GAME)
	{
		delay = 1;
		gg->UpdateGame(wnd.mouse, wnd.kbd, dt);
		std::string message = gg->GetGameMessage();
		if (message == "Exit")
		{
			wnd.Kill();
		}
		if (message == "Menu")
		{
			DestroyGame();
			state = State::MENU;
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

void App::ComposeFrame()
{
	if (state == State::MENU)
	{
		menu->Draw(gfx);
	}

	if (state == State::GAME)
	{
		gg->DrawGame(gfx);
	}
}