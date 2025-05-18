#pragma once
#include "LivingEntity.h"
#include <random>
#include <memory>

class Enemy : public LivingEntity
{
public:
	Enemy(const Vec2& pos_in);
	void Update(GameObject& other, float dt);
	void Heal(float dt) override;
private:
	std::unique_ptr<std::mt19937> rng;
	std::uniform_real_distribution<float> vRand;
	float speed = 50.0f;
	static constexpr int width = 64;
	static constexpr int height = 64;
	static constexpr int maxLives = 4;
	static constexpr Color c = Colors::Red;
};