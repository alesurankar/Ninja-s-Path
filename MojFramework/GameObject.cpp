#include "GameObject.h"

GameObject::GameObject(const Vec2& pos_in, int width_in, int height_in)
	:
	pos(pos_in),
	width(width_in),
	height(height_in)
{}

const Vec2& GameObject::GetPos() const
{
	return pos;
}

Vec2 GameObject::GetCenter() const
{
	Vec2 center = pos + Vec2(float(width) / 2.0f, float(height) / 2.0f);
	return center;
}
