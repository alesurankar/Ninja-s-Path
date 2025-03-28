#include "GameObject.h"

GameObject::GameObject(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in)
	:
	pos(pos_in),
	vel(vel_in),
	width(width_in),
	height(height_in)
{}

Vec2 GameObject::GetPos()
{
	return pos;
}
