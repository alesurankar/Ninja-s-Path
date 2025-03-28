#pragma once
#include "GeneralGame.h"
#include "FrameTimer.h"
#include "Menu.h"

class App
{
public:
	enum class State
	{
		GameOver,
		Menu,
		PlayGame
	};
	App(class MainWindow& wnd);
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  Moije Funkcije              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  Moji Parametri              */
	FrameTimer ft;
	GeneralGame gg;
	State state = State::Menu;
	Menu menu;
	/********************************/
};