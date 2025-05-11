#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "Vec2.h"
#include "Rect.h"
#include <vector>

class Animation
{
public:
	Animation(int x, int y, int width, int height, const Surface& image_in);
	void Draw(const Vec2& pos, Graphics& gfx) const;
private:
	Surface image;
	std::vector<RectI> frame;
};