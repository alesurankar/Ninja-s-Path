#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "Fonts.h"
#include "Button.h"
#include "Mouse.h"
#include "Vec2.h"
#include <vector>
#include <string>

class Menu
{
public:
	enum class MenuType
	{
		MAIN,
		IN_GAME
	};
	Menu(MenuType type_in);
	void Draw(Graphics& gfx) const;
	void Update(const Mouse& mouse);
	static std::string GetLogo(MenuType type);
	std::string GetMenuMessage();
private:
	void TakeEffect(const std::string& effect);
private:
	Vei2 pos;
	std::string message;
	MenuType type;
	Surface logo = Surface("Images\\menu.bmp");
	std::vector<Button> buttons;
};