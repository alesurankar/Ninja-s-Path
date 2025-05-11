#include "Fonts.h"
#include "ImageEffect.h"

Fonts::Fonts(const std::string filename, Color chroma_in)
	:
	sheet(filename),
	glyphWidth(sheet.GetWidth() / nColumns),
	glyphHeight(sheet.GetHeight() / nRows),
	chroma(chroma_in)
{
}

void Fonts::DrawText(const std::string text, const Vei2& pos, Color color, Graphics& gfx) const
{
	auto curPos = pos;
	for (auto chr : text)
	{
		if (chr == '\n')
		{
			curPos.x = pos.x;
			curPos.y += glyphHeight;
			continue;
		}
		else if (chr >= firstChar + 1 && chr <= lastChar)
		{
			gfx.DrawImage(curPos.x, curPos.y, GlyphRect(chr), sheet, ImageEffect::OneColor{chroma, color});
		}
		curPos.x += glyphWidth;
	}
}

RectI Fonts::GlyphRect(char c) const
{
	const int glyphIndex = c - ' ';
	const int yGlyph = glyphIndex / nColumns;
	const int xGlyph = glyphIndex % nColumns;
	return RectI(
		{ xGlyph * glyphWidth, yGlyph * glyphHeight },
		glyphWidth, glyphHeight
	);
}