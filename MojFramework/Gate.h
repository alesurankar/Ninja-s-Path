#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "Camera.h"
#include "Vec2.h"
#include <vector>


class Gate
{
public:
	Gate() = default;
	Gate(const Vei2& positionOffset_in);
	void Draw(const Camera& cam, Graphics& gfx);
private:
	Vei2 positionOffset;
	std::vector<int> grid;
	Surface brick = Surface("Images\\brick32x32.bmp");
public:
	static constexpr int gridSize_x = 6;
	static constexpr int gridSize_y = 7;
	static constexpr int brickWidth = 32;
	static constexpr int brickHeight = 32;
	static constexpr int gridWidth = gridSize_x * brickWidth;
	static constexpr int gridHeight = gridSize_y * brickHeight;
};