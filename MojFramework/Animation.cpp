#include "Animation.h"
#include "ImageEffect.h"

Animation::Animation(int x, int y, int width, int height, int frameCount, const Surface& image_in, float holdTime_in)
	:
	image(image_in),
	holdTime(holdTime_in)
{
	for (int i = 0; i < frameCount; i++)
	{
		frame.emplace_back(x + i * width, y, x + (i + 1) * width, height + y);
	}
}

void Animation::Draw(const Vec2& pos, Graphics& gfx) const
{
	gfx.DrawImage(pos, frame[curFrame], image, ImageEffect::Chroma{Colors::Magenta});
	//gfx.DrawImage(pos, frame[curFrame], image, ImageEffect::NoEffect{ });
}

void Animation::Update(float dt)
{
	frameTime += dt;
	while (frameTime >= holdTime)
	{
		Advance();
		frameTime -= holdTime;
	}
}

void Animation::Advance()
{
	if (++curFrame >= frame.size())
	{
		curFrame = 0;
	}
}