#pragma once

#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float CheckTime();
public:
	std::chrono::steady_clock::time_point last;
};