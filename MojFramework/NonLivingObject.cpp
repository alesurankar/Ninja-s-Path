#include "NonLivingObject.h"

NonLivingObject::NonLivingObject(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in)
	:
	GameObject(pos_in, width_in, height_in),
	object(object_in)
{}

void NonLivingObject::Draw(Graphics & gfx) const
{
	gfx.DrawImage(pos, object, ImageEffect::NoEffect{});
}
