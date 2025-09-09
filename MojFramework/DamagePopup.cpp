#include "DamagePopup.h"


DamagePopup::DamagePopup(int damage_in, Vei2 pos_in)
	:
	damage(damage_in),
	pos(std::move(pos_in))
{}

void DamagePopup::Draw(const Camera& cam, Graphics& gfx)
{
	Vec2 screenPos;
	cam.WorldToScreen(Vec2(pos), screenPos);
	bigFont.DrawText(std::to_string(damage), Vei2(screenPos), Colors::Red, gfx);
}