#include "Gate.h"
#include "ImageEffect.h"


Gate::Gate(const Vei2& positionOffset_in)
	:
	positionOffset(positionOffset_in)
{
	grid = {
		   1,0,1,1,0,1,
		   1,1,1,1,1,1,
		   0,1,0,0,1,0,
		   0,1,1,1,1,0,
		   1,1,1,1,1,1,
		   1,1,0,0,1,1,
		   1,1,0,0,1,1
	};
}

void Gate::Draw(const Camera& cam, Graphics& gfx)
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