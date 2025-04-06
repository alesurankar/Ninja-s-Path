#include "Collectable.h"

Collectable::Collectable(const Vec2& pos_in)
	:
	NonLivingObject(pos_in, Surface("Images\\Point18x18.bmp"), width, height)
{}