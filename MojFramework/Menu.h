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
		SETTINGS
	};
	Menu(MenuType type_in);
	void Draw(Graphics& gfx);
	void Update(const Mouse& mouse);
	void TakeEffect(const std::string& effect);
	static std::string GetLogo(MenuType type);
	std::string GetMessage();
private:
	std::string message;
	MenuType type;
	Surface logo;
	std::vector<Button> buttons;
};