#include "LivingEntity.h"
#include <fstream>

LivingEntity::LivingEntity(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in, const std::string& filename_in, Color c_in)
	:
	GameObject(pos_in, width_in, height_in),
	object(object_in),
	destroyed(false),
	filename(filename_in),
	c(c_in)
{
	LoadFromFile(filename);
	for (int i = (int)Sequence::STANDING_RIGHT; i <= (int)Sequence::STANDING_LEFT; i++)
	{
		animations.emplace_back(0, 0, width, height, 1, object, 1.0f);
	}
	for (int i = (int)Sequence::WALKING_RIGHT; i <= (int)Sequence::COUNT; i++)
	{
		animations.emplace_back(0, 0, width, height, 9, object, 0.06f);
	}
}

void LivingEntity::Draw(Graphics & gfx) const
{
	animations[(int)curSequence].Draw(pos, gfx, facingLeft);
}

void LivingEntity::DrawStatus(Graphics& gfx) const
{
	RectI wholeBar(Vei2(pos) - Vei2(0, 6), width, 5);
	RectI diminBar(Vei2(pos) - Vei2(0, 6), width * hp / maxHP, 5);
	gfx.DrawRect(wholeBar, c);
	gfx.DrawRect(wholeBar, Colors::White);
	gfx.DrawRect(diminBar, c);
}

bool LivingEntity::DestroyedStatus()
{
	return destroyed;
}

void LivingEntity::TakeDamage(LivingEntity& other, int weaponBonus)
{
	if (!destroyed)
	{
		int damageDone = (other.DamageDeal() + weaponBonus) / shield;
		hp -= damageDone;
		if (hp <= 0)
		{
			Destroyed();
			hp = 0;
		}
	}
}

int LivingEntity::DamageDeal()
{
	return power;
}

int LivingEntity::MeleDamage()
{
	return power;
}

void LivingEntity::Destroyed()
{
	destroyed = true;
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

void LivingEntity::SaveToFile(std::string filename)
{
	std::ofstream file(filename);
	if (file)
	{
		file << level << " " << maxHP << " " << hp << " " << maxXP << " " << xp << " " << power << " " << shield << "\n";
	}
}

void LivingEntity::LoadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (file)
	{
		file >> level >> maxHP >> hp >> maxXP >> xp >> power >> shield;
	}
}

void LivingEntity::CollectXP(LivingEntity& other)
{
	int levelDifference = other.GetLevel() - GetLevel();
	if (levelDifference >= -3)
	{
		int xp_increase = other.GetMaxXP() / (8 * GetLevel());
		xp += xp_increase;
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
	maxXP += 300 + 90 * level;//(maxXP * 115) / 100;
	maxHP = (maxHP * 115) / 100;  // +30;
	hp = maxHP;
	power = (power * 115) / 100;
	shield = (shield * 115) / 100;
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
