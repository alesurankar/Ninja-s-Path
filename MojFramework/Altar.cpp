#include "Altar.h"

Altar::Altar(const Vec2& pos_in)
	:
	NonLivingObject(pos_in, Surface("Images\\altar119x119.bmp"), width, height)
{}