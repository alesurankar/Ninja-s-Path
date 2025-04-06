#pragma once
#include "GameObject.h"

class LivingEntity : public GameObject
{
public:
	LivingEntity(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in, int maxLives_in, Color c_in);
	void Draw(Graphics& gfx) const override;
	bool DestroyedStatus();
	void Destroyed();
	void Damaged();
protected:
	Surface object;
	bool destroyed;
	float inOff = 1.0f;
	int maxLives;
	int lives;
	Color c;
};