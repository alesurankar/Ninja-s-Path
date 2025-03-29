#include "LivingEntity.h"

LivingEntity::LivingEntity(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in, float maxHP_in, float power_in, float speed_in, float shield_in)
	:
	GameObject(pos_in, vel_in, width_in, height_in),
	maxHP(maxHP_in),
	hp(maxHP_in),
	power(power_in),
	speed(speed_in),
	shield(shield_in),
	destroyed(false),
	firing(false),
	loaded(false)
{}

void LivingEntity::TakeDamage(LivingEntity& other, float weaponBonus)
{
	const float damageDone = (other.DamageDeal() + weaponBonus) / shield;
	hp -= damageDone;
	if (hp <= 0)
	{
		destroyed = true;
	}
}

float LivingEntity::DamageDeal()
{
	return power;
}

void LivingEntity::Destroyed()
{
	destroyed = true;
}

bool LivingEntity::DestroyedStatus()
{
	return destroyed;
}

float LivingEntity::MeleDamage()
{
	return power;
}

bool LivingEntity::FiringStatus()
{
	return firing;
}

void LivingEntity::Fire()
{
	if (loaded)
	{
		firing = true;
		loaded = false;
	}
	else
	{
		firing = false;
	}
}

void LivingEntity::Reload()
{
	loaded = true;
}