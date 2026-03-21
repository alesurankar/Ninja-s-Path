#include "Enemy.h"

Enemy::Enemy(const Vec2& pos_in)
	:
	LivingEntity(pos_in, Surface("Images\\enemy64x64.bmp"), width, height, ("Config\\enemy_config.txt"), c),
	rng(std::random_device{}()),
	vRand(-1.0f, 1.0f)
{}
void Enemy::Update(LivingEntity& other, float dt)
{
	Vec2 delta = other.GetPos() - GetCenter();
	Vec2 dir = delta;
	if (other.DestroyedStatus() || delta.GetLengthSq() > 40000.f) {
		dir = Vec2(vRand(rng), vRand(rng));
		speed = 10.0f;
	}
	else if (delta.GetLengthSq() > 100.0f) {
		if (delta.y < 0.0f) {
			dir.y -= 1.0f;
		}
		if (delta.y > 0.0f) {
			dir.y += 1.0f;
		}
		if (delta.x < 0.0f) {
			dir.x -= 1.0f;
		}
		if (delta.x > 0.0f) {
			dir.x += 1.0f;
		}
		speed = 40.0f;
	}
	else {
		Vec2 dir(0.0f, 0.0f);
	}
	if (hitColldownTime > 0.0f) {
		hitColldownTime -= dt;
	}
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