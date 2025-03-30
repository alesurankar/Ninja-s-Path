#pragma once
#include "GameObject.h"

class LivingEntity : public GameObject
{
public:
	LivingEntity(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in, float speed_in, int level_in, float maxHP_in, float maxXP_in, float power_in, float shield_in);
	virtual void Draw(Graphics& gfx) const = 0;
	bool FiringStatus();
	void Fire();
	void Reload();
	void CollectXP();
	void TakeDamage(LivingEntity& other, float weaponBonus);
	float DamageDeal();
	void Destroyed();
	bool DestroyedStatus();
	float MeleDamage();
	void LevelUp();
	void SaveToFile(const std::string& filename);
public:
	int level;
	float maxHP;
	float maxXP;
	float power;
	float shield;
	float hp = maxHP;
	float speed;
	bool destroyed;
	bool firing;
	bool loaded;
	float xp = 0;
	float inOff = 1.0f;
};