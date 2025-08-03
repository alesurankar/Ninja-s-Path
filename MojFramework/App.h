#pragma once
#include "Game.h"
#include "FrameTimer.h"
#include "Menu.h"
#include <thread>
#include <memory>
#include <string>
#include "Fonts.h"
#include "ImguiManager.h"
#include "imgui/imgui.h"

class App
{
public:
	enum class State
	{
		MENU,
		GAME
	};
	App(class MainWindow& wnd, std::string username_in);
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
	ImguiManager imgui;
	FrameTimer ft;
	std::unique_ptr<Game> game;
	std::unique_ptr<Menu> menu;
	State state = State::MENU;
	int delay;
	std::string username;
	Fonts bigFont = Fonts("Images\\Fonts16x28.bmp");
	Fonts smallFont = Fonts("Images\\Fonts8x14.bmp");

	ImFont* fontRegular = nullptr;
	ImFont* fontBold = nullptr;
	ImFont* SemiCondensed_Black = nullptr;
	bool show_demo_window = true;
	/********************************/
};