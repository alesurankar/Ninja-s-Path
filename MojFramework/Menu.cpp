#include "Menu.h"

void Menu::Draw(Graphics& gfx) const
{
	gfx.DrawRect(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Black);
	gfx.DrawImage(200, 200, menu);
}
