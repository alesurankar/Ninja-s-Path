#include "MainWindow.h"
#include "App.h"

App::App(MainWindow& wnd, std::atomic<bool>& runFlag, std::shared_ptr<MessageHandler> msgHandler_in)
	:
	wnd(wnd),
	gfx(wnd),
	msgHandler(msgHandler_in),
	running(runFlag),
	nextFrame(true)
{
	//InputThread = std::thread(&App::InputLoop, this);
	CreateMenu();
}

App::~App()
{
	DestroyGame();
	DestroyMenu();
	//if (InputThread.joinable())
	//{
	//	InputThread.join();
	//}
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
		std::string message = menu->GetMessage();
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
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}

	if (state == State::PlayGame)
	{
		gg->UpdateGame(wnd.mouse, wnd.kbd, dt); 
		std::string message = gg->GetGameMessage(); 
		if (message == "Menu")
		{
			DestroyGame();
			state = State::Menu;
			CreateMenu();
		}
		if (message == "Exit")
		{
			wnd.Kill();
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