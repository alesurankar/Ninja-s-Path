#include "Player.h"

Player::Player(const Vec2& pos_in)
	:
	LivingEntity(pos_in, Surface("Images\\player33x58.bmp"), width, height, ("Config\\player_config.txt"), c)
{
}

Player::~Player()
{
	SaveToFile("Config\\player_config.txt");
}

void Player::Draw(const Camera& cam, Graphics& gfx) const
{
	Vec2 screenPos;
	cam.WorldToScreen(pos, screenPos);
	if (!destroyed)
	{
		animations[(int)curSequence].Draw(screenPos, gfx, facingLeft);
	}
	else
	{
		animations[(int)curSequence].DrawGhost(screenPos, gfx, facingLeft);
	}
}

void Player::DrawXP(Graphics& gfx) const
{
	RectI wholeBar(0, gfx.ScreenHeight - 10, gfx.ScreenWidth, gfx.ScreenHeight);
	RectI diminBar(0, gfx.ScreenHeight - 10, (gfx.ScreenWidth * xp / maxXP), gfx.ScreenHeight);
	gfx.DrawRect(wholeBar, Colors::Gray);
	gfx.DrawRect(diminBar, Colors::Yellow);
	smallFont.DrawText("XP: " + std::to_string(xp) + " / " + std::to_string(maxXP), { gfx.ScreenWidth / 2 - 20, gfx.ScreenHeight - 11 }, Colors::Black, gfx);
}

void Player::DrawStatus(Graphics& gfx) const
{
	gfx.DrawImage(0, 0, face, ImageEffect::NoEffect{});
	RectI hpBar(0, 0, (fullHP.GetWidth() * lives / maxLives), fullHP.GetHeight());
	RectI energyBar(0, 0, fullEnergy.GetWidth(), fullEnergy.GetHeight());
	gfx.DrawImage(face.GetWidth(), 0, emptyHP, ImageEffect::Chroma{ Colors::Magenta });
	gfx.DrawImage(face.GetWidth(), 0, hpBar, fullHP, ImageEffect::Chroma{ Colors::Magenta });
	gfx.DrawImage(face.GetWidth(), fullHP.GetHeight(), energyBar, fullEnergy, ImageEffect::Chroma{ Colors::Magenta });
	smallFont.DrawText(std::to_string(maxLives) + " / " + std::to_string(lives), { 100, 10 }, Colors::Black, gfx);
	smallFont.DrawText("Lvl: ", { 340, 10 }, Colors::Yellow, gfx);
	bigFont.DrawText("0", { 370, 10 }, Colors::Yellow, gfx);
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

Vec2 Player::GetDirection(const Camera& cam, const Mouse& mouse)
{
	Vec2 mouseScreenPos = (Vec2)mouse.GetPos();
	Vec2 mouseWorldPos = cam.ScreenToWorld(mouseScreenPos);
	Vec2 playerWorldPos = GetCenter();
	Vec2 dir = mouseWorldPos - playerWorldPos;

	return dir.GetNormalized();
}