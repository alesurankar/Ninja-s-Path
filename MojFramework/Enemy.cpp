#include "Enemy.h"

Enemy::Enemy(const Vec2& pos_in)
	:
	LivingEntity(pos_in, Surface("Images\\SpriteEnemy24x24.bmp"), width, height)
{}
void Enemy::Update(GameObject& other, float dt)
{
	Vec2 delta = other.GetPos() - GetPos();
	Vec2 dir(0.0f, 0.0f);
	if (delta.GetLengthSq() > 100.0f)
	{
		if (delta.y < 0.0f)
		{
			dir.y -= 1.0f;
		}
		if (delta.y > 0.0f)
		{
			dir.y += 1.0f;
		}
		if (delta.x < 0.0f)
		{
			dir.x -= 1.0f;
		}
		if (delta.x > 0.0f)
		{
			dir.x += 1.0f;
		}
	}
	else
	{
		Vec2 dir(0.0f, 0.0f);
	}
	pos += dir.GetNormalized() * speed * dt;
}

//bool Enemy::Colliding(Player& player)
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
//
//bool Enemy::Colliding(Bullet& bul)
//{
//	const float right0 = bul.GetPos().x + bul.GetDim();
//	const float bottom0 = bul.GetPos().y + bul.GetDim();
//	const float right1 = pos.x + width;
//	const float bottom1 = pos.y + height;
//
//	return
//		right0 >= pos.x &&
//		bottom0 >= pos.y &&
//		right1 >= bul.GetPos().x &&
//		bottom1 >= bul.GetPos().y;
//}
//
//bool Enemy::DestroyedStatus()
//{
//	return destroyed;
//}
//
//void Enemy::Damaged()
//{
//	lives--;
//	if (lives <= 0)
//	{
//		destroyed = true;
//	}
//}
//
//Vec2 Enemy::GetPos()
//{
//	return pos;
//}
