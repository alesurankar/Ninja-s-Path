#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "Vec2.h"
#include "Rect.h"
#include <vector>

class Animation
{
public:
	Animation(int x, int y, int width, int height, int frameCount, const Surface& image_in, float holdTime_in);
	void Draw(const Vec2& pos, Graphics& gfx, bool mirrored = false) const;
	void DrawGhost(const Vec2& pos, Graphics& gfx, bool mirrored = false) const;
	void Update(float dt);
private:
	void Advance();
private:
	Surface image;
	std::vector<RectI> frame;
	float holdTime;
	float frameTime = 0.0f;
	int curFrame = 0;
};