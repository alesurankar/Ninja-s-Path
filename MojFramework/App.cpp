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
	gfx.EndFrame();
}

void App::UpdateModel()
{
	float dt = ft.CheckPoint();

	if (state == State::Menu)
	{
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