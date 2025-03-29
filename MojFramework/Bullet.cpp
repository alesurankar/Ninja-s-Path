#include "Bullet.h"

Bullet::Bullet(const Vec2& pos_in, const Vec2& vel_in)
	:
	Projectile(pos_in, vel_in, width, height, speed, damage)
{}

void Bullet::Draw(Graphics& gfx) const
{
	gfx.DrawImage(pos, bullet);
}