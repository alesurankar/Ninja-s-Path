#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in, float speed_in, int damage_in);
public:
	float speed;
	int damage;
	bool smashed;
};