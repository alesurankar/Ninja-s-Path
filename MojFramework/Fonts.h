#pragma once
#include "Graphics.h"
#include "Colors.h"
#include "Surface.h"
#include "Vec2.h"
#include "Rect.h"
#include <string>

class Fonts
{
public:
	Fonts(const std::string filename, Color chroma_in = Colors::White);
	void DrawText(const std::string text, const Vei2& pos, Color color, Graphics& gfx) const; 
	RectI GlyphRect(char c) const;
private:
	Surface sheet;
	int glyphWidth;
	int glyphHeight;
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
	Color chroma;
};