#pragma once
#include "GameObject.h"
#include "Surface.h"

class LivingEntity : public GameObject
{
public:
	LivingEntity(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in, int hp_in, int power_in);
public:
	int hp;
	int power;
	bool destroyed;
};