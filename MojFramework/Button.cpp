#include "Button.h"


Button::Button(int x_in, int y_in, const std::string& text_in)
	:
	x(x_in),
	y(y_in),
	text(text_in),
	outside(x - offset, y - offset, x + width + offset, y + height + offset),
	inside(x, y, x + width, y + height),
	small_middle_x(x + (width / 2) - (len_x / 2)),
	small_middle_y(y + (height / 2) - (len_y / 2)),
	len_x(8 * static_cast<int>(text.length())),
    len_y(14)
{}

void Button::Update(const Mouse& mouse)
{
	Vei2 mousePos = mouse.GetPos();
	if (mousePos.y > y && mousePos.y < (y + height) &&
		mousePos.x > x && mousePos.x < (x + width))
	{
		onTop = true;
	}
	else
	{
		onTop = false;
	}
	if (onTop)
	{
		if (mouse.LeftIsPressed())
		{
			pressed = true;
		}
		else
		{
			pressed = false;
		}
	}
}

void Button::Draw(Graphics & gfx)
{
	if (onTop)
	{
		gfx.DrawRect(outside, Colors::Yellow);
	}
	if (pressed)
	{
		gfx.DrawRect(inside, Colors::DarkBlue);
	}
	else
	{
		gfx.DrawRect(inside, Colors::Blue);
	}
	smallFont.DrawText(text, { small_middle_x, small_middle_y }, Colors::Yellow, gfx);
}