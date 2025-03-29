#pragma once

class Config
{
public:
	static constexpr int offset = 2;
	static constexpr int scoreY = 12;
	static constexpr int yOffset = 3 * offset + scoreY;
public:
	static constexpr int maxScore = 6;
	static constexpr float difficulty = 100.0f;
	static constexpr int enemyNum = 20;
	static constexpr float enemyRespawnTime = 1.0f;
};