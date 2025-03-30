#include "Projectile.h"

Projectile::Projectile(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in, float speed_in, int damage_in)
	:
	GameObject(pos_in, vel_in, width_in, height_in),
	speed(speed_in),
	damage(damage_in),
	smashed(false)
{}

void Projectile::Update(float dt)
{
	pos += vel * speed * dt;
	//center = pos + Vec2(dim / 2, dim / 2);

	BorderCheck();
}

void Projectile::BorderCheck()
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
