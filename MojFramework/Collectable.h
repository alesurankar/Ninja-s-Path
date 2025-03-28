#pragma once

#include "Graphics.h"
#include "Player.h"
#include "Config.h"
#include "Vec2.h"

class Collectable
{
public:
	Collectable(const Vec2& pos_in);
	void BorderCheck();
	void Draw(Graphics& gfx) const;
	bool Colliding(Player& player);
private:
	Surface point = Surface("Images\\Point18x18.bmp");
	Vec2 pos;
	static constexpr float width = 18.0f;
	static constexpr float height = 18.0f;
};