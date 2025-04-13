#include "Bullet.h"

Bullet::Bullet(const Vec2& pos_in, const Vec2& dir_in)
	:
	Projectile(pos_in, Surface("Images\\Bullet6x6.bmp"), width, height),
	dir(dir_in)
{}

void Bullet::Update(const GameObject& other, float dt)
{
	Vec2 distance = other.GetCenter() - GetCenter();
	if (distance.GetLengthSq() > 60000)
	{
		Smashed();
	}
	pos += dir.GetNormalized() * speed * dt;
}