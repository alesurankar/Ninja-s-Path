#pragma once
#include "Graphics.h"
#include "Surface.h"
#include <vector>


class MapGrid
{
public:
	MapGrid(int gridSize_x_in, int gridSize_y_in);
	void Draw(Graphics& gfx);
protected:
	int gridSize_x;
	int gridSize_y;
private:
	std::vector<int> grid;
	static constexpr int width = 32;
	static constexpr int height = 32;
	Surface brick = Surface("Images\\brick32x32.bmp");
};