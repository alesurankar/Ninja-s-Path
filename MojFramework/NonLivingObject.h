#pragma once
#include "GameObject.h"

class NonLivingObject : public GameObject
{
public:
	NonLivingObject(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in);
	void Draw(const Camera& cam, Graphics& gfx) const override;
protected:
	int z;
private:
	Surface object;
};