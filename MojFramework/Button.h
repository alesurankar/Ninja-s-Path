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
	bool GetEffect();
	std::string GetButtonMessage();
	void Pressed();
	void Released();
private:
	int x;
	int y;
	std::string text;
	bool effect;
	bool onTop;
	bool pressed;
	bool released;
	int len_x;
	int len_y;
	int middle_x;
	int middle_y;
	RectI outside;
	RectI inside;
	Fonts bigFont = Fonts("Images\\Fonts16x28.bmp");
	Fonts smallFont = Fonts("Images\\Fonts8x14.bmp");
public:
	static constexpr int width = 140;
	static constexpr int height = 30;
};