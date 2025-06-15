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
		CreateMenu();
		if (wnd.mouse.LeftIsPressed())
		{
			DestroyMenu();
			state = State::PlayGame;
		}
	}

	if (state == State::PlayGame)
	{
		CreateGame();
		gg->UpdateGame(wnd.mouse, wnd.kbd, dt);
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
	if (state == State::Menu)
	{
		menu->Draw(gfx);
	}

	if (state == State::PlayGame)
	{
		gg->DrawGame(gfx);
	}
}