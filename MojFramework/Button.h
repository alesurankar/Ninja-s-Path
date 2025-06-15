#pragma once
#include "Graphics.h"
#include "Mouse.h"
#include "Fonts.h"
#include "Rect.h"
#include "Vec2.h"
#include <string>

class Button
{
public:
	Button(int x_in, int y_in, const std::string& text_in);
	void Draw(Graphics& gfx) const;
	void Update(const Mouse& mouse);
private:
	int x;
	int y;
	std::string text;
	static constexpr int width = 120;
	static constexpr int height = 30;
	Fonts bigFont = Fonts("Images\\Fonts16x28.bmp");
	Fonts smallFont = Fonts("Images\\Fonts8x14.bmp");
	bool onTop;
	bool pressed;
	int len_x;
	int len_y;
	int middle_x;
	int middle_y;
	RectI outside;
	RectI inside;
};