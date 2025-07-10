#include "Camera.h"

Camera::Camera(const Vec2& pos_in)
	:
	pos(pos_in)
{}

void Camera::Follow(const Vec2& targetPos)
{
	pos = targetPos - Vec2((float)Graphics::ScreenWidth, (float)Graphics::ScreenHeight) / 2.0f;
}

void Camera::WorldToScreen(Vec2 worldPos, Vec2& screenPos) const
{
	screenPos = worldPos - pos;
}

Vec2 Camera::ScreenToWorld(Vec2& screenPos) const
{
	return screenPos + pos;
}
