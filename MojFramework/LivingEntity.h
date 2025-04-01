#pragma once
#include "GameObject.h"

class LivingEntity : public GameObject
{
public:
	LivingEntity(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in, float speed_in, int level_in, int maxHP_in, int maxXP_in, int power_in, int shield_in);
	virtual void Draw(Graphics& gfx) const = 0;
	bool FiringStatus();
	void Fire();
	void Reload();
	void TakeDamage(LivingEntity& other, int weaponBonus);
	int DamageDeal();
	void Destroyed();
	bool DestroyedStatus();
	int MeleDamage();
	void CollectXP(LivingEntity& other);
	void LevelUp();
	void SaveToFile(const std::string& filename);
	int GetLevel();
	int GetMaxXP();
public:
	int level;
	int maxHP;
	int maxXP;
	int power;
	int shield;
	int xp;
	int hp;
	float speed;
	bool destroyed;
	bool firing;
	bool loaded;
	float inOff = 1.0f;
	int addXP;
};