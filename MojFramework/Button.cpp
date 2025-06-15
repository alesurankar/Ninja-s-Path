#include "Button.h"

Button::Button(int x_in, int y_in, const std::string& text_in)
	:
	x(x_in),
	y(y_in),
	text(text_in),
	pressed(false),
	onTop(false),
	outside(x - 1, y - 1, x + width + 1, y + height + 1),
	inside(x, y, x + width, y + height),
	len_x(8 * static_cast<int>(text.length())),
	len_y(14),
	middle_x(x + (width/2) - (len_x/2)),
	middle_y(y + (height/2) - (len_y/2))
{}

void Button::Draw(Graphics& gfx) const
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
	smallFont.DrawText(text, {middle_x, middle_y}, Colors::Yellow, gfx);
}

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
