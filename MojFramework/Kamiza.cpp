#include "Kamiza.h"

Kamiza::Kamiza(const Vec2& pos_in)
	:
	NonLivingObject(pos_in, Surface("Images\\kamiza120x120.bmp"), width, height)
{
	//CreateHitBox(padding_LR, padding_TB);
}
