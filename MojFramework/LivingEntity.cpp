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
	for (int i = (int)Sequence::WALKING_RIGHT; i <= (int)Sequence::WALKING_LEFT; i++)
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
	RectI diminBar(Vei2(pos) - Vei2(0, 6), width * lives / maxLives, 5);
	gfx.DrawRect(wholeBar, c);
	gfx.DrawRect(wholeBar, Colors::White);
	gfx.DrawRect(diminBar, c);
	smallFont.DrawText("Lvl 0", Vei2(pos) - Vei2(0, 20), Colors::White, gfx);
}

bool LivingEntity::DestroyedStatus()
{
	return destroyed;
}

void LivingEntity::Destroyed()
{
	destroyed = true;
	lives = 0;
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

void LivingEntity::Damaged()
{
	lives--;
	if (lives <= 0)
	{
		Destroyed();
	}
}

void LivingEntity::SaveToFile(std::string filename)
{
	std::ofstream file(filename);
	if (file)
	{
		file << maxLives << " " << lives << "\n";
	}
}

void LivingEntity::ActiveRegenerate(float dt)
{
	const int percent = maxLives / 20;
	healTime += dt;
	if (healTime > 0.4f)
	{
		Heal(percent);
		healTime = 0.0f;
	}
	if (destroyed && maxLives < lives * 10)
	{
		Respawn();
	}
}

void LivingEntity::PasiveRegenerate(float dt)
{
	const int percent = maxLives / 50;
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
	lives += amount;
	if (lives >= maxLives)
	{
		lives = maxLives;
	}
}

void LivingEntity::LoadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (file)
	{
		file >> maxLives >> lives;
	}
}

void LivingEntity::Respawn()
{
	destroyed = false;
}