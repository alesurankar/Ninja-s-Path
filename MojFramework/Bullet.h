#pragma once
#include "Projectile.h"

class Bullet : public Projectile
{
public:
	Bullet(const Vec2& pos_in, const Vec2& vel_in);
	void Draw(Graphics& gfx) const override;
private:
	Surface bullet = Surface("Images\\Bullet6x6.bmp");
	static constexpr float width = 6.0f;
	static constexpr float height = 6.0f;
	static constexpr float speed = 500.0f;
	static constexpr float damage = 100.0f;
};