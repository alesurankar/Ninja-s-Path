#include "GameObject.h"

GameObject::GameObject(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in)
	:
	pos(pos_in),
	vel(vel_in),
	width(width_in),
	height(height_in)
{}

void GameObject::BorderCheck()
{
	if (pos.x <= float(Config::offset))
	{
		pos.x = float(Config::offset);
		vel.x = -vel.x;
	}
	if (pos.y <= float(Config::yOffset))
	{
		pos.y = float(Config::yOffset);
		vel.y = -vel.y;
	}
	if (pos.x >= float(Graphics::ScreenWidth - Config::offset) - width)
	{
		pos.x = float(Graphics::ScreenWidth - Config::offset) - width;
		vel.x = -vel.x;
	}
	if (pos.y >= float(Graphics::ScreenHeight - Config::offset) - height)
	{
		pos.y = float(Graphics::ScreenHeight - Config::offset) - height;
		vel.y = -vel.y;
	}
}

Vec2 GameObject::GetPos()
{
	return pos;
}

Vec2 GameObject::GetCenter()
{
	return pos + Vec2(width / 2.0f, height / 2.0f);
}

float GameObject::GetWidth()
{
	return width;
}

float GameObject::GetHeight()
{
	return height;
}