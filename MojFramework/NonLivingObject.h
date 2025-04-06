#pragma once
#include "GameObject.h"

class NonLivingObject : public GameObject
{
public:
	NonLivingObject(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in);
	void Draw(Graphics& gfx) const override;
protected:
	Surface object;
};