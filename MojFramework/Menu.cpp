#include "Menu.h"

void Menu::Draw(Graphics& gfx) const
{
	RectI rect(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight);
	gfx.DrawRect(rect, Colors::Black);
	gfx.DrawImage(200, 200, menu);
}
