#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in);
	void Draw(const Camera& cam, Graphics& gfx) const override;
	void Smashed();
	bool SmashedStatus();
	int DamageBonus();
protected:
	int z;
private:
	Surface object;
	int damage = 20;
	bool smashed;
};