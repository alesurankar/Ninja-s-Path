#include "Enemy.h"

Enemy::Enemy(const Vec2& pos_in)
	:
	LivingEntity(pos_in, Surface("Images\\enemy64x64.bmp"), width, height, ("Config/level3_enemy.txt"), c),
	rng(std::make_unique<std::mt19937>(std::random_device{}())),
	vRand(-1.0f, 1.0f)
{}

void Enemy::Update(LivingEntity& other, float dt)
{
	Vec2 delta = other.GetPos() - GetCenter();
	if (delta.GetLengthSq() < 40000.0f && delta.GetLengthSq() > 100.0f)
	{
		speed = 40.0f;
		dir = delta;
	}
	if (other.DestroyedStatus() || delta.GetLengthSq() > 40000.0f)
	{
		dirWalk++;
		if (dirWalk > 20)
		{
			speed = 10.0f;
			dir = Vec2(vRand(*rng), vRand(*rng));
			dirWalk = 0;
		}
	}
	
	if (hitColldownTime > 0.0f)
	{
		hitColldownTime -= dt;
	}
	PassiveRegenerate(dt);
	ReadDirection(dir);
	pos += dir.GetNormalized() * speed * dt;
	animations[(int)curSequence].Update(dt);
}

float Enemy::GetHitColldown()
{
	return hitColldownTime;
}

void Enemy::ResetHitCooldown()
{
	hitColldownTime = constHitCooldownTime;
}
