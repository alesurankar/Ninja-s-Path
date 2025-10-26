#pragma once
#include "Vec2.h"
#include <algorithm>

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
	bool IsOverlappingWith(const Rect_& other) const
	{
		return right > other.left && left < other.right
			&& bottom > other.top && top < other.bottom;
	}
	Vec2_<T> GetCenter() const
	{
		return Vec2_<T>((left + right) / (T)2, (top + bottom) / (T)2);
	}
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