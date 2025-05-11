#include "Menu.h"
#include "ImageEffect.h"

void Menu::Draw(Graphics& gfx) const
{
	RectI rect(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight);
	gfx.DrawRect(rect, Colors::Black);
	bigFont.DrawText("Menu", { 200, 200 }, Colors::Green, gfx);
	smallFont.DrawText("left click...", { 200, 250 }, Colors::Yellow, gfx);
}
