#pragma once
#include "NonLivingObject.h"

class Altar : public NonLivingObject
{
public:
	Altar(const Vec2& pos_in);
private:
	static constexpr int width = 119;
	static constexpr int height = 119;
};