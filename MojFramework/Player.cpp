#include "Player.h"
#include <fstream>

Player::Player(const Vec2& pos_in)
	:
	LivingEntity(pos_in, Vec2(0.0f, 0.0f), width, height, moveSlow, level, maxHP, maxXP, power, shield)
{
	std::ifstream file("Config/player_config.txt");
	if (file)
	{
		file >> level >> maxHP >> hp >> maxXP >> xp >> power >> shield;
	}
}

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
	int hpBarWidth = /*(maxHP > 0) ? */Graphics::ScreenWidth * hp / maxHP +1/* : 0*/;
	int xpBarWidth = /*(maxXP > 0) ? */ImageWidth + Graphics::ScreenWidth * xp / maxXP +1/* : 0*/;

	hpBarWidth = std::clamp(hpBarWidth, 0, Graphics::ScreenWidth);
	xpBarWidth = std::clamp(xpBarWidth, 0, Graphics::ScreenWidth);

	//CharacterImage
	gfx.DrawImage(Vec2(0.0f, 0.0f), player);
	//HealthBar
	gfx.DrawRect(ImageWidth, 0, Graphics::ScreenWidth, HealthBarHeight, Colors::Green);
	gfx.DrawRect((ImageWidth + 2), 2, Graphics::ScreenWidth - 2, HealthBarHeight - 2, Colors::White);
	gfx.DrawRect(ImageWidth, 0, hpBarWidth, HealthBarHeight, Colors::Green);
	//XPBar
	gfx.DrawRect(ImageWidth, HealthBarHeight, Graphics::ScreenWidth, HealthBarHeight + XPBarHeight, Colors::Yellow);
	gfx.DrawRect(ImageWidth + 2, HealthBarHeight + 2, Graphics::ScreenWidth - 2, HealthBarHeight + XPBarHeight - 2, Colors::White);
	gfx.DrawRect(ImageWidth, HealthBarHeight, xpBarWidth, HealthBarHeight + XPBarHeight, Colors::Orange);
}

int Player::CheckXP()
{
	return xp;
}
