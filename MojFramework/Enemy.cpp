#include "Enemy.h"

Enemy::Enemy(const Vec2& pos_in, const Vec2& vel_in)
	:
	LivingEntity(pos_in, vel_in, width, height, maxHP, power, speed, shield)
{}

void Enemy::Draw(Graphics & gfx) const
{
	gfx.DrawImage(pos, s);
	gfx.DrawRect(pos - Vec2(0.0f, 6.0f), width, 5.0f, Colors::Red);
	gfx.DrawRect(pos + Vec2(inOff, inOff - 6.0f), width - 2 * inOff, 5.0f - 2 * inOff, Colors::White);
	gfx.DrawRect(pos - Vec2(0.0f, 6.0f), width * float(hp) / float(maxHP), 5.0f, Colors::Red);
}

void Enemy::Update(float dt)
{
	pos += vel.GetNormalized() * speed * dt;

	BorderCheck();
}