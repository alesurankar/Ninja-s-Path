#include "Enemy.h"

Enemy::Enemy(const Vec2& pos_in, const Vec2& vel_in)
{
	pos = pos_in;
	vel = vel_in;
	lives = maxLives;
	destroyed = false;
}

void Enemy::BorderCheck()
{
	if (pos.x <= float(Config::offset))
	{
		pos.x = float(Config::offset);
		vel.x = -vel.x;
	}
	if (pos.y <= float(Config::yOffset))
	{
		pos.y = float(Config::yOffset);
		vel.y = -vel.y;
	}
	if (pos.x >= float(Graphics::ScreenWidth - Config::offset) - width)
	{
		pos.x = float(Graphics::ScreenWidth - Config::offset) - width;
		vel.x = -vel.x;
	}
	if (pos.y >= float(Graphics::ScreenHeight - Config::offset) - height)
	{
		pos.y = float(Graphics::ScreenHeight - Config::offset) - height;
		vel.y = -vel.y;
	}
}


void Enemy::Draw(Graphics& gfx) const
{
	gfx.DrawImage(pos,s);
	gfx.DrawRect(pos - Vec2(0.0f, 6.0f), width, 5.0f, Colors::Red);
	gfx.DrawRect(pos + Vec2(inOff, inOff - 6.0f), width - 2 * inOff, 5.0f - 2 * inOff, Colors::White);
	gfx.DrawRect(pos - Vec2(0.0f, 6.0f), width * float(lives) / float(maxLives), 5.0f, Colors::Red);
}

void Enemy::Update(float dt)
{
	pos += vel * dt;

	BorderCheck();
}

bool Enemy::Colliding(Player& player)
{
	const float right0 = player.GetPos().x + player.GetWidth();
	const float bottom0 = player.GetPos().y + player.GetHeight();
	const float right1 = pos.x + width;
	const float bottom1 = pos.y + height;

	return
		right0 >= pos.x &&
		bottom0 >= pos.y &&
		right1 >= player.GetPos().x &&
		bottom1 >= player.GetPos().y;
}

bool Enemy::Colliding(Bullet& bul)
{
	const float right0 = bul.GetPos().x + bul.GetDim();
	const float bottom0 = bul.GetPos().y + bul.GetDim();
	const float right1 = pos.x + width;
	const float bottom1 = pos.y + height;

	return
		right0 >= pos.x &&
		bottom0 >= pos.y &&
		right1 >= bul.GetPos().x &&
		bottom1 >= bul.GetPos().y;
}

bool Enemy::DestroyedStatus()
{
	return destroyed;
}

void Enemy::Damaged()
{
	lives--;
	if (lives <= 0)
	{
		destroyed = true;
	}
}

Vec2 Enemy::GetPos()
{
	return pos;
}
