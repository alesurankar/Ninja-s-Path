#include "Menu.h"
#include "ImageEffect.h"

Menu::Menu()
{
	buttons.emplace_back(100, 180, "New Character");
	buttons.emplace_back(100, 220, "Play Now");
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
	}
}
