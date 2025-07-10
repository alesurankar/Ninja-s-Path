#pragma once
#include "GeneralGame.h"
#include "FrameTimer.h"
#include "Menu.h"
#include <thread>

class App
{
public:
	enum class State
	{
		MENU,
		GAME
	};
	App(class MainWindow& wnd);
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
	State state = State::MENU;
	int delay;
	/********************************/
};