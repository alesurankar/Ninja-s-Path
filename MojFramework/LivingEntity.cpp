#include "LivingEntity.h"
#include <fstream>

LivingEntity::LivingEntity(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in, float speed_in, int level_in, float maxHP_in, float maxXP_in, float power_in, float shield_in)
	:
	GameObject(pos_in, vel_in, width_in, height_in),
	level(level_in),
	maxHP(maxHP_in),
	maxXP(maxXP_in),
	power(power_in),
	shield(shield_in),
	hp(maxHP_in),
	speed(speed_in),
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

void LivingEntity::CollectXP()
{
	xp += 45.0f;
	if (xp > maxXP)
	{
		LevelUp();
		SaveToFile("Config/player_config.txt");
	}
}

void LivingEntity::LevelUp()
{
	level++;
	xp -= maxXP;
	maxXP = RoundToOneDecimal(maxXP * 1.2f);
	maxHP += 10*level;
	hp = maxHP;
	power = RoundToOneDecimal(power * 1.2f);
	shield = RoundToOneDecimal(shield * 1.1f);
}

void LivingEntity::SaveToFile(const std::string& filename) 
{
	std::ofstream file(filename);
	if (file) 
	{
		file << level << " " << maxHP << " " << maxXP << " " << power << " " << shield << "\n";
		file.close();
	}
}