#include "LivingEntity.h"
#include <fstream>

LivingEntity::LivingEntity(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in, const std::string& filename_in, Color c_in)
	:
	GameObject(pos_in, width_in, height_in),
	object(object_in),
	destroyed(false),
	filename(filename_in),
	c(c_in),
	firing(false),
	loaded(false)
{
	LoadFromFile(filename);
	for (int i = (int)Sequence::STANDING_RIGHT; i <= (int)Sequence::STANDING_LEFT; i++)
	{
		animations.emplace_back(0, 0, GetWidth(), GetHeight(), 1, object, 1.0f);
	}
	for (int i = (int)Sequence::WALKING_RIGHT; i <= (int)Sequence::WALKING_LEFT; i++)
	{
		animations.emplace_back(0, 0, GetWidth(), GetHeight(), 9, object, 0.06f);
	}
	maxHP = baseHP + (stamina * 10);
}

void LivingEntity::Draw(const Camera& cam, Graphics& gfx) const
{
	Vec2 screenPos;
	cam.WorldToScreen(GetPos(), screenPos);
	animations[(int)curSequence].Draw(screenPos, gfx, facingLeft);
	DrawStatus(cam, gfx);
}

void LivingEntity::DrawStatus(const Camera& cam, Graphics& gfx) const
{
	Vec2 screenPos;
	cam.WorldToScreen(GetPos(), screenPos);
	RectI wholeBar(Vei2(screenPos) - Vei2(0, 6), GetWidth(), 5);
	RectI diminBar(Vei2(screenPos) - Vei2(0, 6), GetWidth() * hp / maxHP, 5);
	gfx.DrawRect(wholeBar, c);
	gfx.DrawRect(wholeBar, Colors::White);
	gfx.DrawRect(diminBar, c);
	smallFont.DrawText("Lvl " + std::to_string(level), Vei2(screenPos) - Vei2(0, 20), Colors::White, gfx);
}

bool LivingEntity::DestroyedStatus()
{
	return destroyed;
}

int LivingEntity::TakeDamage(LivingEntity& attacker, int weaponBonus)
{
	int finalDamage = 0;
	if (!destroyed)
	{
		int baseDamage = attacker.DamageDeal() + weaponBonus;

		// Optional: add randomness or critical hit chance
		// baseDamage *= CritMultiplierOrVariance();

		float armourReduction = static_cast<float>(armour) /
			(static_cast<float>(armour) + 400.0f + 85.0f * attacker.GetLevel());
		finalDamage = std::max(1, int(baseDamage * (1.0f - armourReduction)));

		hp -= finalDamage;
		if (hp <= 0)
		{
			Destroyed();
			hp = 0;
		}
	}
	return finalDamage;
}

int LivingEntity::DamageDeal()
{
	return strength;
}

int LivingEntity::MeleDamage()
{
	int weaponBase = 1;
	int power = 0;
	int meleDamage = weaponBase + static_cast<int>(strength * 1.5) + power;
	return meleDamage;
}

void LivingEntity::Destroyed()
{
	destroyed = true;
	hp = 0;
}

void LivingEntity::ReadDirection(Vec2 dir)
{

	if (dir.x < 0.0f)
	{
		curSequence = Sequence::WALKING_LEFT;
		facingLeft = true;
	}
	else if (dir.x > 0.0f)
	{
		curSequence = Sequence::WALKING_RIGHT;
		facingLeft = false;
	}
	else if (dir.x == 0.0f)
	{
		if (dir.y != 0)
		{
			if (curSequence == Sequence::WALKING_LEFT || curSequence == Sequence::STANDING_LEFT)
			{
				curSequence = Sequence::WALKING_LEFT;
				facingLeft = true;
			}
			else if (curSequence == Sequence::WALKING_RIGHT || curSequence == Sequence::STANDING_RIGHT)
			{
				curSequence = Sequence::WALKING_RIGHT;
				facingLeft = false;
			}
		}
		else if (dir.y == 0)
		{
			if (curSequence == Sequence::WALKING_LEFT || curSequence == Sequence::STANDING_LEFT)
			{
				curSequence = Sequence::STANDING_LEFT;
				facingLeft = true;
			}
			else if (curSequence == Sequence::WALKING_RIGHT || curSequence == Sequence::STANDING_RIGHT)
			{
				curSequence = Sequence::STANDING_RIGHT;
				facingLeft = false;
			}
		}
	}
}

bool LivingEntity::FiringStatus()
{
	return firing;
}

void LivingEntity::Fire()
{
	if (!DestroyedStatus() && loaded)
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
	firing = false;
	loaded = true;
}

void LivingEntity::ActiveRegenerate(float dt)
{
	const int percent = maxHP / 20;
	healTime += dt;
	if (healTime > 0.4f)
	{
		Heal(percent);
		healTime = 0.0f;
	}
	if (destroyed && maxHP < hp * 10)
	{
		Respawn();
	}
}

void LivingEntity::PasiveRegenerate(float dt)
{
	const int percent = maxHP / 50;
	if (!destroyed)
	{
		healTime += dt;
		if (healTime > 2.0f)
		{
			Heal(percent);
			healTime = 0.0f;
		}
	}
}

void LivingEntity::Heal(int amount)
{
	hp += amount;
	if (hp >= maxHP)
	{
		hp = maxHP;
	}
}

void LivingEntity::SaveToFile(std::string filename)
{
	std::ofstream file(filename);
	if (file)
	{
		file << level << " " << hp << " " << maxXP << " " << xp << " " << " " << stamina << " " << strength << " " << armour << "\n";
	}
}

void LivingEntity::LoadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (file)
	{
		file >> level >> hp >> maxXP >> xp >> stamina >> strength >> armour;
	}
}

void LivingEntity::CollectXP(LivingEntity& other)
{
	//int levelDifference = other.GetLevel() - GetLevel();
	//if (levelDifference >= -3)
	//{
	//	int xp_increase = other.GetMaxXP() / (8 * GetLevel());
	//	xp += xp_increase;
	//	if (xp > maxXP)
	//	{
	//		xp_increase = xp - maxXP;
	//		LevelUp();
	//		xp = xp_increase / ((8 * GetLevel()) / (8 * (GetLevel() - 1)));
	//	}
	//}

	/////////////////

	int levelDifference = other.GetLevel() - GetLevel();
	if (levelDifference >= -3)
	{
		int xp_increase = other.GetMaxXP() / (8 * GetLevel());
		xp += xp_increase * 1; //Faster leveling
		if (xp > maxXP)
		{
			xp_increase = xp - maxXP;
			LevelUp();
			xp = xp_increase / ((8 * GetLevel()) / (8 * (GetLevel() - 1)));
		}
	}
}

void LivingEntity::LevelUp()
{
	level++;
	maxXP += 300 + 90 * level;
	stamina += 3;
	maxHP = 100 + (stamina * 10);
	strength += 2;
	armour += 2;
	hp = maxHP;
}

int LivingEntity::GetLevel()
{
	return level;
}

int LivingEntity::GetMaxXP()
{
	return maxXP;
}

void LivingEntity::Respawn()
{
	destroyed = false;
}
