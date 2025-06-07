#include "Menu.h"
#include "ImageEffect.h"

void Menu::Draw(Graphics& gfx)
{
	RectI rect(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight);
	gfx.DrawRect(rect, Colors::Black);
	DrawButton(160, 160, "Play now!", gfx);
}

void Menu::DrawButton(int x, int y, std::string text, Graphics& gfx)
{
	const int width = 100;
	const int height = 30;
	const int offset = 1;
	const int len_x = 8 * static_cast<int>(text.length());
	const int len_y = 14;
	const int small_middle_x = x + (width / 2) - (len_x / 2);
	const int small_middle_y = y + (height / 2) - (len_y / 2);
	RectI outside(x - offset, y - offset, x + width + offset, y + height + offset);
	RectI inside(x, y, x + width, y + height);
	gfx.DrawRect(outside, Colors::Yellow);
	gfx.DrawRect(inside, Colors::Blue);
	smallFont.DrawText(text, { small_middle_x, small_middle_y }, Colors::Yellow, gfx);
}
