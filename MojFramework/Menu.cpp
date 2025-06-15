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
		pos = Vei2{ 0,0 };
		buttons.emplace_back(100, 180, "New Character");
		buttons.emplace_back(100, 220, "Play now");
		buttons.emplace_back(600, 400, "Exit");
	}
	if (type == MenuType::IN_GAME)
	{
		pos = Vei2{ 240,90 };
		buttons.emplace_back(pos.x + 70, pos.y + 130, "Close");
		buttons.emplace_back(pos.x + 70, pos.y + 230, "Quit to Main Menu");
		buttons.emplace_back(pos.x + 70, pos.y + 270, "Quit and Exit");
	}
}

void Menu::Draw(Graphics& gfx) const
{
	gfx.DrawImage(pos.x, pos.y, logo, ImageEffect::NoEffect{});
	for (auto& b : buttons)
	{
		b.Draw(gfx);
	}
}

void Menu::Update(const Mouse& mouse)
{
	for (auto& b : buttons)
	{
		b.Update(mouse);
		if (b.GetEffect())
		{
			TakeEffect(b.GetButtonMessage());
		}
	}
}

std::string Menu::GetLogo(MenuType type)
{
	switch (type)
	{
	case MenuType::MAIN:
		return "Images\\menu.bmp";
	case MenuType::IN_GAME:
		return "Images\\menu2.bmp";
	default:
		return std::string();
	}
}

std::string Menu::GetMenuMessage()
{
	return message;
}

void Menu::TakeEffect(const std::string& effect)
{
	message = effect;
}
