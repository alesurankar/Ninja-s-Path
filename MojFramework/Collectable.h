#pragma once
#include "NonLivingObject.h"

class Collectable : public NonLivingObject
{
public:
	Collectable(const Vec2& pos_in);
private:
	static constexpr int width = 18;
	static constexpr int height = 18;
};