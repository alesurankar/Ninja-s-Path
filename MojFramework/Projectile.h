#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in, float speed_in, int damage_in);
	void Update(float dt);
	void BorderCheck();
	void Smashed();
	bool SmashedStatus();
	int DamageBonus();
public:
	int damage;
	float speed;
	bool smashed;
};