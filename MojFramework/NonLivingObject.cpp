#include "NonLivingObject.h"

NonLivingObject::NonLivingObject(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in)
	:
	GameObject(pos_in, width_in, height_in),
	object(object_in)
{
	padding_LR = float(width_in / 5);
	padding_TB = float(height_in / 5);
}

void NonLivingObject::Draw(const Camera& cam, Graphics & gfx) const
{
	Vec2 screenPos;
	Vec2 boxScreenPos;
	cam.WorldToScreen(pos, screenPos);
	cam.WorldToScreen(GetCenter(), boxScreenPos);
	gfx.DrawImage(screenPos, object, ImageEffect::Chroma{Colors::Magenta});
	gfx.DrawRectThin((RectI)GetHitbox(boxScreenPos, padding_LR, padding_TB), Colors::Blue);
}
