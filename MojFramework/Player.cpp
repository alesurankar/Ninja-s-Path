#include "Player.h"

Player::Player(const Vec2& pos_in)
	:
	LivingEntity(pos_in, Surface("Images\\SpriteMe21x36.bmp"), width, height, maxLives, c),
	firing(false),
	loaded(false)
{}

void Player::Update(const Mouse& mouse, const Keyboard& kbd, float dt)
{
	if (mouse.LeftIsPressed())
	{
		Fire();
	}
	else
	{
		Reload();
	}
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

bool Player::FiringStatus()
{
	return firing;
}

void Player::Fire()
{
	if (loaded)
	{
		firing = true;
		loaded = false;
	}
	else
	{
		firing = false;
	}
}

void Player::Reload()
{
	firing = false;
	loaded = true;
}

Vec2 Player::GetDirection(const Mouse& mouse)
{
	Vec2 dir = Vec2(mouse.GetPos()) - GetCenter();
	return dir.GetNormalized();
}