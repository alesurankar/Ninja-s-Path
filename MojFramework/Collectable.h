#pragma once

#include "Graphics.h"
#include "Jaz.h"
#include "GeneralGame.h"
#include "Vec2.h"

class Collectable
{
public:
	void Init(const Vec2& pos_in);
	void BorderCheck();
	void Draw(Graphics& gfx) const;
	bool Colliding(Jaz& jaz);
private:
	Vec2 pos;
	static constexpr float width = 18.0f;
	static constexpr float height = 18.0f;
};