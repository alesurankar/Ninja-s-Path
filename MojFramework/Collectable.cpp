#include "Collectable.h"



Collectable::Collectable(const Vec2& pos_in)
{
	pos = pos_in;
}

void Collectable::BorderCheck()
{
	if (pos.x <= float(Config::offset))
	{
		pos.x = float(Config::offset);
	}
	if (pos.y <= float(Config::yOffset))
	{
		pos.y = float(Config::yOffset);
	}
	if (pos.x >= float(Graphics::ScreenWidth - Config::offset) - width)
	{
		pos.x = float(Graphics::ScreenWidth - Config::offset) - width;
	}
	if (pos.y >= float(Graphics::ScreenHeight - Config::offset) - height)
	{
		pos.y = float(Graphics::ScreenHeight - Config::offset) - height;
	}
}

void Collectable::Draw(Graphics& gfx) const
{
	gfx.DrawImage(pos, point);
}

bool Collectable::Colliding(Player& player)
{
	const float right0 = player.GetPos().x + player.GetWidth();
	const float bottom0 = player.GetPos().y + player.GetHeight();
	const float right1 = pos.x + width;
	const float bottom1 = pos.y + height;

	return
		right0 >= pos.x &&
		bottom0 >= pos.y &&
		right1 >= player.GetPos().x &&
		bottom1 >= player.GetPos().y;
}