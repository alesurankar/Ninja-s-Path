#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "Fonts.h"
#include "Button.h"
#include "Mouse.h"
#include <vector>
#include <string>

class Menu
{
public:
	Menu();
	void Draw(Graphics& gfx) const;
	void Update(const Mouse& mouse);
	std::string GetMenuMessage();
private:
	void TakeEffect(const std::string& effect);
private:
	std::string message;
	Surface logo = Surface("Images\\menu.bmp");
	std::vector<Button> buttons;
};