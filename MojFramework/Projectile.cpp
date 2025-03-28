#include "Projectile.h"

Projectile::Projectile(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in, float speed_in, int damage_in)
	:
	GameObject(pos_in, vel_in, width_in, height_in),
	speed(speed_in),
	damage(damage_in),
	smashed(false)
{}
