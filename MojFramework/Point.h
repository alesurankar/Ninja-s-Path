#pragma once
#include "NonLivingObject.h"
#include "Player.h"

class Point : public NonLivingObject
{
public:
	Point(const Vec2& pos_in);
	void Draw(Graphics& gfx) const override;
private:
	Surface point = Surface("Images\\Point18x18.bmp");
	static constexpr float width = 18.0f;
	static constexpr float height = 18.0f;
};