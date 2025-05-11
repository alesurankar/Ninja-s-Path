#include "Animation.h"

Animation::Animation(int x, int y, int width, int height, const Surface& image_in)
	:
	image(image_in)
{
	frame.emplace_back(x, y, width + x, height + y);
}

void Animation::Draw(const Vec2& pos, Graphics& gfx) const
{
	gfx.DrawImage(pos, frame[0], image);
}
