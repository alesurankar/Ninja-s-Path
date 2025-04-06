#include "Collectable.h"

Collectable::Collectable(const Vec2& pos_in)
	:
	NonLivingObject(pos_in, Surface("Images\\Point18x18.bmp"), width, height)
{}

//bool Collectable::Colliding(Player& player)
//{
//	const float right0 = player.GetPos().x + player.GetWidth();
//	const float bottom0 = player.GetPos().y + player.GetHeight();
//	const float right1 = pos.x + width;
//	const float bottom1 = pos.y + height;
//
//	return
//		right0 >= pos.x &&
//		bottom0 >= pos.y &&
//		right1 >= player.GetPos().x &&
//		bottom1 >= player.GetPos().y;
//}