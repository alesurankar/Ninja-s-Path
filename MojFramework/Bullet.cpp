#include "Bullet.h"

Bullet::Bullet(const Vec2& center_in, const Vec2& vel_in)
{
	center = center_in;
	pos = center - Vec2(dim/2, dim/2);
	vel = vel_in;
	smashed = false;
}

void Bullet::Draw(Graphics& gfx) const
{
	gfx.DrawCircle(center, dim / 2, Colors::White);
}

void Bullet::Update(float dt)
{
	pos += vel * speed * dt;
	center = pos + Vec2(dim / 2, dim / 2);

	BorderCheck();
}

void Bullet::BorderCheck()
{
	if (pos.x <= float(GeneralGame::offset))
	{
		Smashed();
	}
	if (pos.y <= float(GeneralGame::yOffset))
	{
		Smashed();
	}
	if (pos.x >= float(Graphics::ScreenWidth - GeneralGame::offset) - dim)
	{
		Smashed();
	}
	if (pos.y >= float(Graphics::ScreenHeight - GeneralGame::offset) - dim)
	{
		Smashed();
	}
}

void Bullet::Smashed()
{
	smashed = true;
}

bool Bullet::SmashedStatus()
{
	return smashed;
}

Vec2 Bullet::GetPos()
{
	return pos;
}

float Bullet::GetDim()
{
	return dim;
}
