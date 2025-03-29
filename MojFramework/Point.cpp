#include "Point.h"


Point::Point(const Vec2& pos_in)
	:
	NonLivingObject(pos_in, width, height)
{}

void Point::Draw(Graphics& gfx) const
{
	gfx.DrawImage(pos, point);
}