#pragma once
#include "LivingEntity.h"

class Enemy : public LivingEntity
{
public:
	Enemy(const Vec2& pos_in);
	void Update(GameObject& other, float dt);
	void Heal(float dt) override;
private:
	float speed = 50.0f;
	static constexpr int width = 64;
	static constexpr int height = 64;
	static constexpr Color c = Colors::Red;
};