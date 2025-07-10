#pragma once
#include "Vec2.h"
#include "Graphics.h"

class Camera
{
public:
	Camera(const Vec2& pos_in);
	void Follow(const Vec2& targetPos);
	void WorldToScreen(Vec2 worldPos, Vec2& screenPos) const;
	Vec2 ScreenToWorld(Vec2& screenPos) const;
private:
	Vec2 pos;
};