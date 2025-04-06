#include "Player.h"

Player::Player(const Vec2& pos_in)
	:
	LivingEntity(pos_in, Surface("Images\\SpriteMe21x36.bmp"), width, height)
{}

void Player::Update(const Mouse& mouse, const Keyboard& kbd, float dt)
{
	//if (mouse.LeftIsPressed())
	//{
	//	Fire();
	//}
	//else
	//{
	//	Reload();
	//}
	if (kbd.KeyIsPressed(VK_SPACE))
	{
		speed = Config::mySpeed * 3;
	}
	else
	{
		speed = Config::mySpeed;
	}

	Vec2 dir(0.0f, 0.0f);
	if (kbd.KeyIsPressed('W'))
	{
		dir.y -= 1.0f;
	}
	if (kbd.KeyIsPressed('S'))
	{
		dir.y += 1.0f;
	}
	if (kbd.KeyIsPressed('A'))
	{
		dir.x -= 1.0f;
	}
	if (kbd.KeyIsPressed('D'))
	{
		dir.x += 1.0f;
	}
	pos += dir.GetNormalized() * speed * dt;
}

//Vec2 Player::GetPos()
//{
//	return pos;
//}
//
//float Player::GetWidth()
//{
//	return width;
//}
//
//float Player::GetHeight()
//{
//	return height;
//}
//
//bool Player::FiringStatus()
//{
//	return firing;
//}
//
//void Player::Fire()
//{
//	if (loaded)
//	{
//		firing = true;
//		loaded = false;
//	}
//	else
//	{
//		firing = false;
//	}
//}
//
//void Player::Reload()
//{
//	loaded = true;
//}
//
//Vec2 Player::GetCenter()
//{
//	return pos + Vec2(width / 2.0f, height / 2.0f);
//}
//
//Vec2 Player::GetDirection(const Mouse& mouse)
//{
//	Vec2 dir = Vec2(float(mouse.GetPosX()), float(mouse.GetPosY())) - GetCenter();
//	return dir.GetNormalized();
//}
//
//void Player::Destroyed()
//{
//	destroyed = true;
//}
//
//bool Player::DestroyedStatus()
//{
//	return destroyed;
//}
//
//void Player::Damaged()
//{
//	lives--;
//	if (lives <= 0)
//	{
//		Destroyed();
//	}
//}
