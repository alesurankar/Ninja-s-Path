#include "Menu.h"
#include "ImageEffect.h"

Menu::Menu()
{
	buttons.emplace_back(100, 180, "New Character");
	buttons.emplace_back(100, 220, "Play now");
	buttons.emplace_back(600, 400, "Quit");
}

void Menu::Draw(Graphics& gfx) const
{
	gfx.DrawImage(0, 0, logo, ImageEffect::NoEffect{});
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

std::string Menu::GetMenuMessage()
{
	return message;
}

void Menu::TakeEffect(const std::string& effect)
{
	message = effect;
}
