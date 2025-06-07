#include "Menu.h"
#include "ImageEffect.h"

Menu::Menu(MenuType type_in)
	:
	type(type_in),
	logo("Images\\menu.bmp")
{
	buttons.clear();
	if (type == MenuType::MAIN)
	{
		buttons.emplace_back(100, 180, "New Character");
		buttons.emplace_back(100, 220, "Play now");
		buttons.emplace_back(600, 400, "Exit");
	}
	else if (type == MenuType::IN_GAME)
	{
		buttons.emplace_back(200, 200, "Quit to Main Menu");
		buttons.emplace_back(200, 240, "Quit to Exit");
		buttons.emplace_back(240, 280, "Close");
	}
}

void Menu::Update(const Mouse& mouse)
{
	for (auto& b : buttons)
	{
		b.Update(mouse);
		if (b.GetEffect())
		{
			TakeEffect(b.GetText());
		}
	}
}

void Menu::TakeEffect(const std::string& effect)
{
	message = effect;
}

std::string Menu::GetMessage()
{
	return message;
}

void Menu::Draw(Graphics& gfx)
{
	gfx.DrawImage(0, 0, logo, ImageEffect::NoEffect{});
	for (auto& b : buttons)
	{
		b.Draw(gfx);
	}
}