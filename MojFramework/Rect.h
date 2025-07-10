#pragma once
#include "Vec2.h"

template<typename T>
class Rect_
{
public:
	Rect_(T left_in, T top_in, T right_in, T bottom_in)
		:
		left(left_in),
		top(top_in),
		right(right_in),
		bottom(bottom_in)
	{}
	Rect_(const Vec2_<T>& topLeft, const Vec2_<T>& bottomRight)
		:
		Rect_(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y)
	{}
	Rect_(const Vec2_<T>& topLeft, T width, T height)
		:
		Rect_(topLeft, topLeft + Vec2_<T>(width, height))
	{}
	T GetWidth() const
	{
		return right - left;
	}
	T GetHeight() const
	{
		return bottom - top;
	}
public:
	T left;
	T top;
	T right;
	T bottom;
};

using RectI = Rect_<int>;
using RectF = Rect_<float>;