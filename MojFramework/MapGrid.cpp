#include "MapGrid.h"
#include "ImageEffect.h"


MapGrid::MapGrid(int gridSize_x_in, int gridSize_y_in)
	:
	gridSize_x(gridSize_x_in),
	gridSize_y(gridSize_y_in)
{
	grid = {
		   1,0,1,1,1,
		   0,1,1,1,1,
		   1,0,1,0,0,
		   1,1,0,0,1
	};
}

void MapGrid::Draw(Graphics& gfx)
{
	int k = 0;
	for (int j = 0; j < gridSize_y; j++)
	{
		int y = j * height;
		for (int i = 0; i < gridSize_x; i++)
		{
			int x = i * width;
			if (grid[k] == 1)
			{
				gfx.DrawImage(x, y, brick, ImageEffect::NoEffect{});
			}
			k++;
		}
	}
}
