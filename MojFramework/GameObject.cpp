#include "GameObject.h"

GameObject::GameObject(const Vec2& pos_in, int width_in, int height_in)
	:
	pos(pos_in),
	width(width_in),
	height(height_in)
{}

bool GameObject::Colliding(GameObject& other)
{
	const float right0 = other.GetPos().x + other.GetWidth();
	const float bottom0 = other.GetPos().y + other.GetHeight();
	const float right1 = pos.x + width;
	const float bottom1 = pos.y + height;

	return
		right0 >= pos.x &&
		bottom0 >= pos.y &&
		right1 >= other.GetPos().x &&
		bottom1 >= other.GetPos().y;
}

const Vec2& GameObject::GetPos() const
{
	return pos;
}

Vec2 GameObject::GetCenter() const
{
	Vec2 center = pos + Vec2(float(width) / 2.0f, float(height) / 2.0f);
	return center;
}

int GameObject::GetWidth() const
{
	return width;
}

int GameObject::GetHeight() const
{
	return height;
}
