#pragma once
#include "MessageHandler.h"
#include "GeneralGame.h"
#include "FrameTimer.h"
#include "Menu.h"
#include <string>

class App
{
public:
	enum class State
	{
		GameOver,
		Menu,
		PlayGame
	};
	App(class MainWindow& wnd, std::atomic<bool>& runFlag, std::shared_ptr<MessageHandler> msgHandler_in);
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	~App();
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  Moje Funkcije               */
	void CreateGame();
	void DestroyGame();
	void CreateMenu();
	void DestroyMenu();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  Moji Parametri              */
	FrameTimer ft;
	GeneralGame* gg = nullptr;
	Menu* menu = nullptr;
	State state = State::Menu;
	std::shared_ptr<MessageHandler> msgHandler;
	std::thread InputThread;
	std::atomic<bool>& running;
	std::atomic<bool> nextFrame;
	/********************************/
};