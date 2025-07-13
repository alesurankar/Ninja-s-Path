#pragma once
#include "Gate.h"
#include "Wall.h"
#include "Vec2.h"
#include "Graphics.h"
#include <vector>


class Fortres
{
public:
	Fortres(Vei2 pos_in);
	void Draw(const Camera& cam, Graphics& gfx);
private:
	Vei2 pos;
	std::vector<Gate> gate;
	std::vector<Wall> wall;
};