#pragma once

#include "Graphics.h"
#include "Config.h"
#include "Surface.h"

class Menu
{
public:
	void Draw(Graphics& gfx) const;
private:
	Surface menu = Surface("Images\\GameMenu 400x200.bmp");
};