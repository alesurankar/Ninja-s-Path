#pragma once
#include "LivingEntity.h"
#include "Player.h"
#include "Bullet.h"

class Enemy : public LivingEntity
{
public:
	Enemy(const Vec2& pos_in, const Vec2& vel_in);
	void Draw(Graphics& gfx) const override;
	void Update(float dt);
private:
	Surface s = Surface("Images\\SpriteEnemy24x24.bmp");
	static constexpr float width = 24.0f;
	static constexpr float height = 24.0f;
	static constexpr float maxHP = 300.0f;
	static constexpr float power = 4.0f;
	static constexpr float speed = 150.0f;
	static constexpr float shield = 10.0f;
};