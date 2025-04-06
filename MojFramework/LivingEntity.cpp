#include "LivingEntity.h"

LivingEntity::LivingEntity(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in)
	:
	GameObject(pos_in, width_in, height_in),
	object(object_in),
	destroyed(false)
{}

void LivingEntity::Draw(Graphics & gfx) const
{
	gfx.DrawImage(pos, object);
	//gfx.DrawRect(pos - Vec2(0.0f, 6.0f), width, 5.0f, Colors::Green);
	//gfx.DrawRect(pos + Vec2(inOff, inOff - 6.0f), width - 2 * inOff, 5.0f - 2 * inOff, Colors::White);
	//gfx.DrawRect(pos - Vec2(0.0f, 6.0f), width * float(lives) / float(maxLives), 5.0f, Colors::Green);
}

bool LivingEntity::DestroyedStatus()
{
	return destroyed;
}

void LivingEntity::Destroyed()
{
	destroyed = true;
}
