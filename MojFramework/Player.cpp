#include "Player.h"

Player::Player(const Vec2& pos_in)
	:
	LivingEntity(pos_in, Vec2(0.0f, 0.0f), width, height, maxHP, power, moveSlow, shield)
{}

void Player::Draw(Graphics& gfx) const
{
	gfx.DrawImage(pos, s);
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
	if (kbd.KeyIsPressed(VK_SPACE))
	{
		speed = moveFast;
	}
	else
	{
		speed = moveSlow;
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

	BorderCheck();
}

Vec2 Player::GetDirection(const Mouse& mouse)
{
	Vec2 dir = Vec2(float(mouse.GetPosX()), float(mouse.GetPosY())) - GetCenter();
	return dir.GetNormalized();
}

void Player::ShowHP(Graphics& gfx) const
{
	gfx.DrawRect(0, 0, Graphics::ScreenWidth, Config::scoreY + 2*Config::offset, Colors::Green);
	gfx.DrawRect(Config::offset, Config::offset, Graphics::ScreenWidth - Config::offset, Config::scoreY + Config::offset, Colors::White);
	gfx.DrawRect(Config::offset, Config::offset, Graphics::ScreenWidth * int(hp) / int(maxHP) - Config::offset, Config::scoreY + Config::offset, Colors::Green);
}