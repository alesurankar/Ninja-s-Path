#pragma once
#include "LivingEntity.h"
#include <random>
#include <memory>

class Enemy : public LivingEntity
{
public:
	Enemy(const Vec2& pos_in);
	void Update(LivingEntity& other, float dt);
	float GetHitColldown();
	void ResetHitCooldown();
private:
	std::unique_ptr<std::mt19937> rng;
	std::uniform_real_distribution<float> vRand;
	float speed = 50.0f;
	static constexpr int width = 64;
	static constexpr int height = 64;
	static constexpr Color c = Colors::Red; 
	static constexpr float constHitCooldownTime = 2.0f;
	float hitColldownTime = constHitCooldownTime;
	int dirWalk = 0;
	Vec2 dir = Vec2(vRand(*rng), vRand(*rng));
};