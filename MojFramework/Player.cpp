#include "Player.h"

Player::Player(const Vec2& pos_in)
	:
	LivingEntity(pos_in, Surface("Images\\player33x58.bmp"), width, height, ("Config\\player_config.txt"), c),
	firing(false),
	loaded(false)
{}

Player::~Player()
{
	SaveToFile("Config\\player_config.txt");
}

void Player::Draw(Graphics& gfx) const
{
	if (!destroyed)
	{
		animations[(int)curSequence].Draw(pos, gfx, facingLeft);
	}
	else
	{
		animations[(int)curSequence].DrawGhost(pos, gfx, facingLeft);
	}
}

void Player::DrawStatus(Graphics& gfx) const
{
	gfx.DrawImage(0, 0, face, ImageEffect::NoEffect{});
	RectI wholeBar(36, 0, gfx.ScreenWidth / 2, 40);
	RectI diminBar(36, 0, (gfx.ScreenWidth * lives / maxLives) / 2, 40);
	gfx.DrawRect(wholeBar, Colors::White);
	gfx.DrawRect(diminBar, c);
	smallFont.DrawText(std::to_string(maxLives) + " / " + std::to_string(lives), { 100, 10 }, Colors::Black, gfx);
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
	PasiveRegenerate(dt);
	ReadDirection(dir);
	pos += dir.GetNormalized() * speed * dt;
	animations[(int)curSequence].Update(dt);
}

bool Player::FiringStatus()
{
	return firing;
}

void Player::Fire()
{
	if (!DestroyedStatus() && loaded)
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