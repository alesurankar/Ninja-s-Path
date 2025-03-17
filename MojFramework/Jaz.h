#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Config.h"
#include "Vec2.h"
#include "Surface.h"

class Jaz
{
public:
	Jaz(const Vec2& pos_in);
	void BorderCheck();
	void Draw(Graphics& gfx) const;
	void Update(const Mouse& mouse, const Keyboard& kbd, float dt);
	Vec2 GetPos();
	float GetWidth();
	float GetHeight();
	bool FiringStatus();
	void Fire();
	void Reload();
	Vec2 GetCenter();
	Vec2 GetDirection(const Mouse& mouse);
	void Destroyed();
	void Respawn();
	bool DestroyedStatus();
	void Damaged();
private:
	Surface s = Surface("Images\\SpriteMe21x36.bmp");
	float inOff = 1.0f;
	bool destroyed = false;
	int lives;
	bool firing;
	bool loaded;
	Vec2 pos;
	float speed;
	static constexpr float width = 21.0f;
	static constexpr float height = 36.0f;
	static constexpr int maxLives = Config::myLives;
};