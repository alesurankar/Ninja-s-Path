#pragma once
#include "Colors.h"
#include "Graphics.h"

namespace ImageEffect
{
	class Chroma
	{
	public:
		Chroma(Color chroma_in)
			:
			chroma(chroma_in)
		{}
		void operator()(Color color, int x, int y, Graphics& gfx) const
		{
			if (color != chroma)
			{
				gfx.PutPixel(x, y, color);
			}
		}
	private:
		Color chroma;
	};

	class NoEffect
	{
	public:
		void operator()(Color color, int x, int y, Graphics& gfx) const
		{
			gfx.PutPixel(x, y, color);
		}
	};

	class OneColor
	{
	public:
		OneColor(Color chroma_in, Color color_in)
			:
			chroma(chroma_in),
			oneColor(color_in)
		{}
		void operator()(Color color, int x, int y, Graphics& gfx) const
		{
			if (color != chroma)
			{
				gfx.PutPixel(x, y, oneColor);
			}
		}
	private:
		Color chroma;
		Color oneColor;
	};
}