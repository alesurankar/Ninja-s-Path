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
	enum class MenuType
	{
		MAIN,
		IN_GAME
	};
	Menu(MenuType type_in);
	void Draw(Graphics& gfx);
	void Update(const Mouse& mouse);
	void TakeEffect(const std::string& effect);
	std::string GetMessage();
private:
	std::string message;
	Surface logo;
	std::vector<Button> buttons;
	MenuType type;
};