#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include "Config.h"
#include "Keyboard.h"
#include "Mouse.h"

class GameObject
{
public:
	GameObject(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in); 
	virtual void Draw(Graphics& gfx) const = 0;
	bool Colliding(GameObject& other);
	void BorderCheck();
	Vec2 GetPos();
	float GetWidth();
	float GetHeight();
	Vec2 GetCenter();
public:
	Vec2 pos;
	Vec2 vel;
	float width;
	float height;
};