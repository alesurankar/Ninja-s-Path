#include "LivingEntity.h"

LivingEntity::LivingEntity(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in, int maxLives_in, Color c_in)
	:
	GameObject(pos_in, width_in, height_in),
	object(object_in),
	destroyed(false),
	maxLives(maxLives_in),
	lives(maxLives_in),
	c(c_in)
{}

void LivingEntity::Draw(Graphics & gfx) const
{
	gfx.DrawImage(pos, object);
	gfx.DrawRect(pos - Vec2(0.0f, 6.0f), float(width), 5.0f, c);
	gfx.DrawRect(pos + Vec2(inOff, inOff - 6.0f), float(width) - 2.0f * inOff, 5.0f - 2.0f * inOff, Colors::White);
	gfx.DrawRect(pos - Vec2(0.0f, 6.0f), float(width) * float(lives) / float(maxLives), 5.0f, c);
}

bool LivingEntity::DestroyedStatus()
{
	return destroyed;
}

void LivingEntity::Destroyed()
{
	destroyed = true;
}

void LivingEntity::Damaged()
{
	lives--;
	if (lives <= 0)
	{
		Destroyed();
	}
}