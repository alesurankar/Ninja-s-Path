#pragma once
#include "GeneralGame.h"
#include "FrameTimer.h"
#include "Menu.h"
#include <thread>
#include <memory>

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
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  Moje Funkcije               */
	void CreateState();
	void DestroyState();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  Moji Parametri              */
	FrameTimer ft;
	std::unique_ptr<GeneralGame> gg;
	std::unique_ptr<Menu> menu;
	State state = State::MENU;
	int delay;
	/********************************/
};