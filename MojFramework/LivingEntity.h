#pragma once
#include "GameObject.h"

class LivingEntity : public GameObject
{
public:
	LivingEntity(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in, float maxHP_in, float power_in, float speed_in, float shield_in);
	virtual void Draw(Graphics& gfx) const = 0;
	bool FiringStatus();
	void Fire();
	void Reload();
	void TakeDamage(LivingEntity& other, float weaponBonus);
	float DamageDeal();
	void Destroyed();
	bool DestroyedStatus();
	float MeleDamage();
public:
	float maxHP;
	float hp;
	float power;
	float speed;
	float shield;
	bool destroyed;
	bool firing;
	bool loaded;
	float inOff = 1.0f;
};