#include "Enemy.h"

Enemy::Enemy(const Vec2& pos_in)
	:
	LivingEntity(pos_in, Surface("Images\\enemy64x64.bmp"), width, height, ("Config\\enemy_config.txt"), c)
{}
void Enemy::Update(GameObject& other, float dt)
{
	Vec2 delta = other.GetPos() - GetPos();
	Vec2 dir(0.0f, 0.0f);
	if (delta.GetLengthSq() > 100.0f)
	{
		if (delta.y < 0.0f)
		{
			dir.y -= 1.0f;
		}
		if (delta.y > 0.0f)
		{
			dir.y += 1.0f;
		}
		if (delta.x < 0.0f)
		{
			dir.x -= 1.0f;
		}
		if (delta.x > 0.0f)
		{
			dir.x += 1.0f;
		}
	}
	else
	{
		Vec2 dir(0.0f, 0.0f);
	}
	ReadDirection(dir);
	pos += dir.GetNormalized() * speed * dt;
	animations[(int)curSequence].Update(dt);
}

void Enemy::Heal(float dt)
{
}
