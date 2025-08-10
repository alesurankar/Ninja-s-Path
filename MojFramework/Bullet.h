#pragma once
#include "Projectile.h"

class Bullet : public Projectile
{
public:
	Bullet(const Vec2& pos_in, const Vec2& dir_in);
	void Update(const GameObject& other, float dt);
private:
	Vec2 dir;
	static constexpr int width = 6;
	static constexpr int height = 6;
	static constexpr float speed = 500.0f;
	float padding_LR = 1.0f;
	float padding_TB = 1.0f;
};