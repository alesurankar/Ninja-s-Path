#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include "Config.h"

class GameObject
{
public:
	GameObject(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in);
	Vec2 GetPos();
public:
	Vec2 pos;
	Vec2 vel;
	float width;
	float height;
};