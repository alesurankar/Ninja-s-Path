#include "Player.h"

Player::Player(const Vec2& pos_in)
	:
	LivingEntity(pos_in, Vec2(0.0f, 0.0f), width, height, maxHP, power, speed, shield)
{}

void Player::Draw(Graphics& gfx) const
{
	gfx.DrawImage(pos, s);
	gfx.DrawRect(pos - Vec2(0.0f, 6.0f), width, 5.0f, Colors::Green);
	gfx.DrawRect(pos + Vec2(inOff, inOff - 6.0f), width - 2 * inOff, 5.0f - 2 * inOff, Colors::White);
	gfx.DrawRect(pos - Vec2(0.0f, 6.0f), width * float(hp) / float(maxHP), 5.0f, Colors::Green);
}

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
	/*if (kbd.KeyIsPressed(VK_SPACE))
	{
		if (!speedIncreesed)
		{
			speed *= 3;
			speedIncreesed = true;
		}
	}
	else
	{
		if (speedIncreesed)
		{
			speed /= 3;
			speedIncreesed = false;
		}
	}*/
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

	BorderCheck();
}

Vec2 Player::GetDirection(const Mouse& mouse)
{
	Vec2 dir = Vec2(float(mouse.GetPosX()), float(mouse.GetPosY())) - GetCenter();
	return dir.GetNormalized();
}
