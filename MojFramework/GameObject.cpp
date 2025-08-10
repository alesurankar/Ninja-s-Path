#include "GameObject.h"

GameObject::GameObject(const Vec2& pos_in, int width_in, int height_in)
	:
	pos(pos_in),
	width(width_in),
	height(height_in)
{}

bool GameObject::Colliding(GameObject& other)
{
	return GetRect().IsOverlappingWith(other.GetRect());
}

const Vec2& GameObject::GetPos() const
{
	return pos;
}

void GameObject::SetPos(Vec2 pos_in)
{
	pos = pos_in;
}

Vec2 GameObject::GetCenter() const
{
	return GetRect().GetCenter();
}

RectF GameObject::GetRect() const
{
	return RectF(pos, float(width), float(height));
}

int GameObject::GetWidth() const
{
	return width;
}

int GameObject::GetHeight() const
{
	return height;
}

RectF GameObject::GetHitBox(Vec2 camPos_in) const
{
	return hitbox.OffsetBy(camPos_in);
}

void GameObject::CreateHitBox(float padding_LR, float padding_TB)
{
	hitbox = RectF::FromCenter(pos, hitbox_halfwidth - padding_LR, hitbox_halfheight - padding_TB);
}
