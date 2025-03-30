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
public:
	static constexpr float speed = 100.0f;
	static constexpr float width = 24.0f;
	static constexpr float height = 24.0f;
};