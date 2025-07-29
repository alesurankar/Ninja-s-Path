#include "MainWindow.h"
#include "App.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

App::App(MainWindow& wnd, std::string username_in)
	:
	wnd(wnd),
	gfx(wnd),
	username(std::move(username_in))
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
	// imgui stuff
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	static bool show_demo_window = true;
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	switch (state)
	{
	case State::MENU:
		menu->Draw(gfx);
		break;
	case State::GAME:
		game->DrawGame(gfx);
		break;
	}
	smallFont.DrawText(username, { Graphics::ScreenWidth - 240, 70 }, Colors::White, gfx);
}