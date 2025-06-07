#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "Fonts.h"
#include "Mouse.h"
#include "Button.h"
#include <vector>

class Menu
{
public:
	Menu();
	void Draw(Graphics& gfx);
	void Update(const Mouse& mouse);
private:
	Surface logo = Surface("Images\\menu.bmp");
	std::vector<Button> buttons;
};