#include "Projectile.h"

Projectile::Projectile(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in)
	:
	GameObject(pos_in, width_in, height_in),
	object(object_in),
	smashed(false)
{}

void Projectile::Draw(Graphics & gfx) const
{
	gfx.DrawImage(pos, object);
}

void Projectile::Smashed()
{
	smashed = true;
}

bool Projectile::SmashedStatus()
{
	return smashed;
}

