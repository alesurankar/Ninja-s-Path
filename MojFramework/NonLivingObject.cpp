#include "NonLivingObject.h"

NonLivingObject::NonLivingObject(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in)
	:
	GameObject(pos_in, width_in, height_in),
	object(object_in)
{}

void NonLivingObject::Draw(const Camera& cam, Graphics & gfx) const
{
	Vec2 screenPos;
	cam.WorldToScreen(pos, screenPos);
	gfx.DrawImage(screenPos, object, ImageEffect::Chroma{Colors::Magenta});
}
