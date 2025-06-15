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

	class Ghost
	{
	public:
		Ghost(Color chroma_in)
			:
			chroma(chroma_in)
		{}
		void operator()(Color color, int x, int y, Graphics& gfx) const
		{
			if(color != chroma)
			{
				const Color dest = gfx.GetPixel(x, y);
				const Color blend =
				{
					unsigned char((color.GetR() + dest.GetR()) / 3),
					unsigned char((color.GetG() + dest.GetG()) / 3),
					unsigned char((color.GetB() + dest.GetB()) / 3)
				};
				gfx.PutPixel(x, y, blend);
			}
		}
	private:
		Color chroma;
	};
}