#include "MainWindow.h"
#include "App.h"

App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	CreateState();
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
			DestroyState();
			state = State::GAME;
			CreateState();
		}
	}

	if (state == State::GAME)
	{
		delay = 1;
		game->UpdateGame(wnd.mouse, wnd.kbd, dt);
		std::string message = game->GetGameMessage();
		if (message == "Exit")
		{
			wnd.Kill();
		}
		if (message == "Menu")
		{
			DestroyState();
			state = State::MENU;
			CreateState();
		}
	}
}

void App::CreateState()
{
	switch (state)
	{
	case State::MENU:
		menu = std::make_unique<Menu>(Menu::MenuType::MAIN);
		break;
	case State::GAME:
		game = std::make_unique<Game>();
		break;
	}
}

void App::DestroyState()
{
	switch (state)
	{
	case State::MENU:
		menu.reset();
		break;
	case State::GAME:
		game.reset();
		break;
	}
}

void App::ComposeFrame()
{
	switch (state)
	{
	case State::MENU:
		menu->Draw(gfx);
		break;
	case State::GAME:
		game->DrawGame(gfx);
		break;
	}
}