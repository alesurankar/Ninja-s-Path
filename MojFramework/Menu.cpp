#include "Menu.h"
#include "ImageEffect.h"

Menu::Menu(MenuType type_in)
	:
	type(type_in),
	logo(GetLogo(type))
{
	buttons.clear();
	const int logo_x_mid = logo.GetWidth() / 2;
	const int logo_y_mid = logo.GetHeight() / 2;
	const int screen_x_mid = Graphics::ScreenWidth / 2;
	const int screen_y_mid = Graphics::ScreenHeight / 2;
	const int left = screen_x_mid - logo_x_mid;
	const int right = screen_x_mid + logo_x_mid;
	const int top = screen_y_mid - logo_y_mid;
	const int bottom = screen_y_mid + logo_y_mid;
	pos = Vei2{ left, top };
	if (type == MenuType::MAIN) {
		buttons.emplace_back(left + 40, top + 180, "New Character");
		buttons.emplace_back(left + 40, top + 220, "Play now");
		buttons.emplace_back(right - Button::width - 40, bottom - 100, "Exit");
	}
	if (type == MenuType::IN_GAME) {
		buttons.emplace_back(left + 70, top + 130, "Close");
		buttons.emplace_back(left + 70, top + 230, "Quit to Main Menu");
		buttons.emplace_back(left + 70, top + 270, "Quit and Exit");
	}
}

void Menu::Draw(Graphics& gfx) const
{
	gfx.DrawImage(pos.x, pos.y, logo, ImageEffect::Chroma{Colors::Magenta});
	for (auto& b : buttons) {
		b.Draw(gfx);
	}
}

void Menu::Update(const Mouse& mouse)
{
	for (auto& b : buttons) {
		b.Update(mouse);
		if (b.GetEffect()) {
			TakeEffect(b.GetButtonMessage());
		}
	}
}

std::string Menu::GetLogo(MenuType type)
{
	switch (type)
	{
	case MenuType::MAIN:
		return "Images\\menu.bmp";
	case MenuType::IN_GAME:
		return "Images\\menu2.bmp";
	default:
		return std::string();
	}
}

std::string Menu::GetMenuMessage()
{
	return message;
}

void Menu::TakeEffect(const std::string& effect)
{
	message = effect;
}
