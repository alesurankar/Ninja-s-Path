#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Vec2.h"
#include "Config.h"
#include "Surface.h"
#include "ImageEffect.h"
#include "Camera.h"
#include "Rect.h"

class GameObject
{
public:
	GameObject(const Vec2& pos_in, int width_in, int height_in);
	virtual void Draw(const Camera& cam, Graphics& gfx) const = 0;
	bool Colliding(GameObject& other);
	const Vec2& GetPos() const;
	void SetPos(Vec2 pos_in);
	Vec2 GetCenter() const;
	RectF GetRect() const;
	int GetWidth() const;
	int GetHeight() const;
protected:
	Vec2 pos;
	//Vec2 draw_offset = { float(-width/2), float(-height) };
private:
	int width;
	int height;
};