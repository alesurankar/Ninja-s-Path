#include "Fortres.h"

Fortres::Fortres(Vei2 pos_in)
	:
	pos(std::move(pos_in))
{
	int p = 0; 
	int xOffset = 0;	
	int yOffset = Gate::gridHeight - Wall::gridHeight;
	for (int m = 0; m < 21; m++)
	{
		if (p == 0)
		{
			gate.emplace_back(Vei2(pos.x + xOffset, pos.y));
			xOffset += Gate::gridWidth;
			p++;
		}
		else if (p > 0 && p <= 3)
		{
			wall.emplace_back(Vei2(pos.x + xOffset, pos.y + yOffset));
			xOffset += Wall::gridWidth;
			p++;

			if (p > 3) p = 0;
		}
	}
}

void Fortres::Draw(const Camera& cam, Graphics& gfx)
{
	for (auto& g : gate)
	{
		g.Draw(cam, gfx);
	}
	for (auto& w : wall)
	{
		w.Draw(cam, gfx);
	}
}
