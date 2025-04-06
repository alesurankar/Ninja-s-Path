#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Vec2.h"
#include "Config.h"
#include "Surface.h"

class GameObject
{
public:
	GameObject(const Vec2& pos_in, int width_in, int height_in);
	virtual void Draw(Graphics& gfx) const = 0;
	const Vec2& GetPos() const;
	Vec2 GetCenter() const;
public:
	Vec2 pos;
	int width;
	int height;
};