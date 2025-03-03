#include "Collectable.h"



void Collectable::Init(const Vec2& pos_in)
{
	pos = pos_in;
}

void Collectable::BorderCheck()
{
	if (pos.x <= float(GeneralGame::offset))
	{
		pos.x = float(GeneralGame::offset);
	}
	if (pos.y <= float(GeneralGame::yOffset))
	{
		pos.y = float(GeneralGame::yOffset);
	}
	if (pos.x >= float(Graphics::ScreenWidth - GeneralGame::offset) - width)
	{
		pos.x = float(Graphics::ScreenWidth - GeneralGame::offset) - width;
	}
	if (pos.y >= float(Graphics::ScreenHeight - GeneralGame::offset) - height)
	{
		pos.y = float(Graphics::ScreenHeight - GeneralGame::offset) - height;
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