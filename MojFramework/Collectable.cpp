#include "Collectable.h"



void Collectable::Init(const Vec2& pos_in)
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
	gfx.DrawRect(pos, width, height, Colors::Blue);
}

bool Collectable::Colliding(Jaz& jaz)
{
	const float right0 = jaz.GetPos().x + jaz.GetWidth();
	const float bottom0 = jaz.GetPos().y + jaz.GetHeight();
	const float right1 = pos.x + width;
	const float bottom1 = pos.y + height;

	return
		right0 >= pos.x &&
		bottom0 >= pos.y &&
		right1 >= jaz.GetPos().x &&
		bottom1 >= jaz.GetPos().y;
}