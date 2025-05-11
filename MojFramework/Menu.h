#pragma once
#include "Graphics.h"
#include "Config.h"
#include "Surface.h"
#include "Fonts.h"

class Menu
{
public:
	void Draw(Graphics& gfx) const;
private:
	Fonts bigFont = Fonts("Images\\Fonts16x28.bmp");
	Fonts smallFont = Fonts("Images\\Fonts8x14.bmp");
};