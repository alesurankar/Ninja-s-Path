#pragma once
#include "GameObject.h"

class LivingEntity : public GameObject
{
public:
	LivingEntity(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in, const std::string& filename_in, Color c_in);
	void Draw(Graphics& gfx) const override;
	bool DestroyedStatus();
	void Damaged();
	void SaveToFile(std::string filename);
private:
	void LoadFromFile(const std::string& filename);
	void Destroyed();
protected:
	std::string filename;
	Surface object;
	bool destroyed;
	float inOff = 1.0f;
	int maxLives;
	int lives;
	Color c;
};