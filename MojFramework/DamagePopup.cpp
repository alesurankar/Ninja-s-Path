#include "DamagePopup.h"

void DamagePopup::Draw(const Camera& cam, Graphics& gfx)
{
	Vec2 screenPos;
	cam.WorldToScreen(Vec2(pos), screenPos);
	bigFont.DrawText(std::to_string(damage), Vei2(screenPos), Colors::Red, gfx);
}