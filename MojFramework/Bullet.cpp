#include "Bullet.h"

Bullet::Bullet(const Vec2& pos_in, const Vec2& dir_in)
	:
	Projectile(pos_in, Surface("Images\\Bullet6x6.bmp"), width, height),
	dir(dir_in)
{}

void Bullet::Update(float dt)
{
	pos += dir.GetNormalized() * speed * dt;

	BorderCheck();
}

void Bullet::BorderCheck()
{
	if (pos.x <= float(Config::offset))
	{
		Smashed();
	}
	if (pos.y <= float(Config::yOffset))
	{
		Smashed();
	}
	if (pos.x >= float(Graphics::ScreenWidth - Config::offset) - width)
	{
		Smashed();
	}
	if (pos.y >= float(Graphics::ScreenHeight - Config::offset) - height)
	{
		Smashed();
	}
}