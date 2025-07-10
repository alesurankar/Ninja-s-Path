#pragma once
#include "NonLivingObject.h"

class Kamiza : public NonLivingObject
{
public:
	Kamiza(const Vec2& pos_in);
private:
	static constexpr int width = 120;
	static constexpr int height = 120;
};