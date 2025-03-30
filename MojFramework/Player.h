#pragma once
#include "LivingEntity.h"


class Player : public LivingEntity
{
public:
	Player(const Vec2& pos_in);
	void Draw(Graphics& gfx) const override;
	void Update(const Mouse& mouse, const Keyboard& kbd, float dt);
	Vec2 GetDirection(const Mouse& mouse);
	void DrawStats(Graphics& gfx) const;
	int CheckXP();
private:
	Surface player = Surface("Images\\Player36x40.bmp");
	Surface s = Surface("Images\\SpriteMe21x36.bmp");
public:
	static constexpr float width = 21.0f;
	static constexpr float height = 36.0f;
	static constexpr float moveSlow = 200.0f;
	static constexpr float moveFast = 400.0f;
	static constexpr int ImageWidth = 36;
	static constexpr int ImageHeight = 40;
	static constexpr int HealthBarHeight = 32;
	static constexpr int XPBarHeight = 8;
};