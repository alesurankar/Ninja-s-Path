#pragma once
#include "LivingEntity.h"


class Player : public LivingEntity
{
public:
	Player(const Vec2& pos_in);
	void Draw(Graphics& gfx) const override;
	void Update(const Mouse& mouse, const Keyboard& kbd, float dt);
	Vec2 GetDirection(const Mouse& mouse);
private:
	Surface s = Surface("Images\\SpriteMe21x36.bmp");
	static constexpr float width = 21.0f;
	static constexpr float height = 36.0f;
	static constexpr float maxHP = 600.0f;
	static constexpr float power = 6.0f;
	static constexpr float speed = 200.0f;
	static constexpr float shield = 6.0f;
};