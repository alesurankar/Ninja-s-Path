#include "Wall.h"
#include "ImageEffect.h"


Wall::Wall(const Vei2& positionOffset_in)
	:
	positionOffset(positionOffset_in)
{
	grid = {
		   0,1,1,0,
		   1,1,1,1,
		   1,1,1,1,
		   1,1,1,1
	};
}

void Wall::Draw(const Camera& cam, Graphics& gfx)
{
	Vei2 brickPos;
	int k = 0;
	for (int j = 0; j < gridSize_y; j++)
	{
		brickPos.y = (j * brickHeight) + positionOffset.y;
		for (int i = 0; i < gridSize_x; i++)
		{
			brickPos.x = (i * brickWidth) + positionOffset.x;
			Vec2 screenPos;
			cam.WorldToScreen(Vec2(brickPos), screenPos);
			if (grid[k] == 1)
			{
				gfx.DrawImage(screenPos, brick, ImageEffect::NoEffect{});
			}
			k++;
		}
	}
}