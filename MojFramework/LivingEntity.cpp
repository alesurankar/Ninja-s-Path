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
}

void LivingEntity::Draw(Graphics & gfx) const
{
	gfx.DrawImage(pos, { 0,0,width, height }, object);
	RectI wholeBar(Vei2(pos) - Vei2(0, 6), width, 5);
	RectI diminBar(Vei2(pos) - Vei2(0, 6), width * lives / maxLives, 5);
	gfx.DrawRect(wholeBar, c);
	gfx.DrawRect(wholeBar, Colors::White);
	gfx.DrawRect(diminBar, c);
}

bool LivingEntity::DestroyedStatus()
{
	return destroyed;
}

void LivingEntity::Destroyed()
{
	destroyed = true;
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

void LivingEntity::LoadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (file)
	{
		file >> maxLives >> lives;
	}
}