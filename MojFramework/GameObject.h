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
	RectF GetHitbox(Vec2 pos_in, float padding_LR = 0.0f, float padding_TB = 0.0f) const;
	void SetHitBox(const RectF& hitbox_in);
protected:
	Vec2 pos;
	//Vec2 draw_offset = { float(-width/2), float(-height) };
private:
	RectF hitbox;
	int width;
	int height;
	float hitbox_halfwidth = float(width)/2.0f;
	float hitbox_halfheight = float(height)/2.0f;
};