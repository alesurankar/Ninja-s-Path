#include "Player.h"

Player::Player(const Vec2& pos_in)
	:
	LivingEntity(pos_in, Vec2(0.0f, 0.0f), width, height, maxHP, maxXP, power, moveSlow, shield)
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

void Player::DrawStats(Graphics& gfx) const
{
	//CharacterImage
	gfx.DrawImage(Vec2(0.0f, 0.0f), player);
	//HealthBar
	gfx.DrawRect(ImageWidth, 0, Graphics::ScreenWidth, HealthBarHeight, Colors::Green);
	gfx.DrawRect((ImageWidth + 2), 2, Graphics::ScreenWidth - 2, HealthBarHeight - 2, Colors::White);
	gfx.DrawRect(ImageWidth, 0, Graphics::ScreenWidth * int(hp) / int(maxHP), HealthBarHeight, Colors::Green);
	//XPBar
	gfx.DrawRect(ImageWidth, HealthBarHeight, Graphics::ScreenWidth, HealthBarHeight + XPBarHeight, Colors::Yellow);
	gfx.DrawRect(ImageWidth + 2, HealthBarHeight + 2, Graphics::ScreenWidth - 2, HealthBarHeight + XPBarHeight - 2, Colors::White);
	gfx.DrawRect(ImageWidth, HealthBarHeight, ImageWidth + (Graphics::ScreenWidth * int(xp) / int(maxXP)), HealthBarHeight + XPBarHeight, Colors::Orange);

}

float Player::CheckXP()
{
	return xp;
}
