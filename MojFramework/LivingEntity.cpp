#include "LivingEntity.h"
#include <fstream>

LivingEntity::LivingEntity(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in, float speed_in, int level_in, int maxHP_in, int maxXP_in, int power_in, int shield_in)
	:
	GameObject(pos_in, vel_in, width_in, height_in),
	level(level_in),
	maxHP(maxHP_in),
	maxXP(maxXP_in),
	power(power_in),
	shield(shield_in),
	speed(speed_in),
	destroyed(false),
	firing(false),
	loaded(false)
{}

void LivingEntity::TakeDamage(LivingEntity& other, int weaponBonus)
{
	int damageDone = (other.DamageDeal() + weaponBonus) / shield;
	hp -= damageDone;
	if (hp <= 0)
	{
		destroyed = true;
	}
}

int LivingEntity::DamageDeal()
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

int LivingEntity::MeleDamage()
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

void LivingEntity::CollectXP(LivingEntity& other)
{
	int levelDifference = other.GetLevel() - GetLevel();
	if (levelDifference >= -3)
	{
		int xp_increase = other.GetMaxXP() / ((4 * GetLevel() * GetLevel()) / other.GetLevel());
		xp += xp_increase;
		if (xp > maxXP)
		{
			xp_increase = xp - maxXP;
			LevelUp();
			xp = xp_increase / ((4 * GetLevel() * GetLevel()) / other.GetLevel());
			//SaveToFile("Config/player_config.txt");
		}
	}
}

void LivingEntity::LevelUp()
{
	level++;
	maxXP = (maxXP * 115) / 100;
	maxHP = (maxHP * 115) / 100;  // +30;
	hp = maxHP;
	power = (power * 115) / 100;
	shield = (shield * 115) / 100;
}

void LivingEntity::SaveToFile(const std::string& filename) 
{
	std::ofstream file(filename);
	if (file) 
	{
		file << level << " " << maxHP << " " << hp << " " << maxXP << " " << xp << " " << power << " " << shield << "\n";
		file.close();
	}
}

int LivingEntity::GetLevel()
{
	return level;
}

int LivingEntity::GetMaxXP()
{
	return maxXP;
}
