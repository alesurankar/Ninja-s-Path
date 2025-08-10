#include "Projectile.h"

Projectile::Projectile(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in)
	:
	GameObject(pos_in, width_in, height_in),
	object(object_in),
	smashed(false)
{
}

void Projectile::Draw(const Camera& cam, Graphics& gfx) const
{
	Vec2 screenPos;
	Vec2 boxScreenPos;
	cam.WorldToScreen(pos, screenPos);
	cam.WorldToScreen(GetCenter(), boxScreenPos);
	gfx.DrawImage(screenPos, object, ImageEffect::NoEffect{});
	RectF hitbox = GetHitbox(boxScreenPos, 1.0f, 1.0f);
	gfx.DrawRectThin(RectI(hitbox), Colors::Yellow);
}

void Projectile::Smashed()
{
	smashed = true;
}

bool Projectile::SmashedStatus()
{
	return smashed;
}

int Projectile::DamageBonus()
{
	return damage;
}

