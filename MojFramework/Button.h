#pragma once
#include "Fonts.h"
#include "Graphics.h"
#include "Mouse.h"
#include "Vec2.h"
#include "Rect.h"


class Button
{
public:
	Button(int x_in, int y_in, const std::string& text_in);
	void Draw(Graphics& gfx);
	void Update(const Mouse& mouse);
	bool GetEffect();
	std::string GetText();
private:
	void Pressed();
	void Released();
private:
	int x;
	int y;
	std::string text;
	static constexpr int width = 120;
	static constexpr int height = 30;
	static constexpr int offset = 1;
	bool onTop;
	bool pressed;
	bool released;
	bool effect;
	int len_x;
	int len_y;
	int small_middle_x;
	int small_middle_y;
	RectI outside;
	RectI inside;
	Fonts bigFont = Fonts("Images\\Fonts16x28.bmp");
	Fonts smallFont = Fonts("Images\\Fonts8x14.bmp");
};