#include "Menu.h"
#include "ImageEffect.h"

Menu::Menu(MenuType type_in)
	:
	type(type_in),
	logo(GetLogo(type))
{
	buttons.clear();
	if (type == MenuType::MAIN)
	{
		buttons.emplace_back(100, 180, "New Character");
		buttons.emplace_back(100, 220, "Play now");
		buttons.emplace_back(600, 400, "Exit");
	}
	else if (type == MenuType::SETTINGS)
	{
		buttons.emplace_back(250, 220, "Close");
		buttons.emplace_back(250, 320, "Quit to Main Menu");
		buttons.emplace_back(250, 360, "Quit and Exit");
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

std::string Menu::GetLogo(MenuType type)
{
	switch (type)
	{
	case MenuType::MAIN:
		return "Images\\menu.bmp";
	case MenuType::SETTINGS:
		return "Images\\menu2.bmp";
	}
	return std::string();
}

std::string Menu::GetMessage()
{
	return message;
}

void Menu::Draw(Graphics& gfx)
{
	if (type == MenuType::MAIN)
	{
		gfx.DrawImage(0, 0, logo, ImageEffect::NoEffect{});
	}
	else if (type == MenuType::SETTINGS)
	{
		gfx.DrawImage(180, 90, logo, ImageEffect::Chroma{Colors::Magenta});
	}
	for (auto& b : buttons)
	{
		b.Draw(gfx);
	}
}