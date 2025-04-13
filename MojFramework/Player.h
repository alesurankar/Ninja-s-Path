#pragma once
#include "LivingEntity.h"

class Player : public LivingEntity
{
public:
	Player(const Vec2& pos_in);
	void Update(const Mouse& mouse, const Keyboard& kbd, float dt);
	bool FiringStatus();
	void Fire();
	void Reload();
	Vec2 GetDirection(const Mouse& mouse);
private:
	bool firing;
	bool loaded;
	float speed = 100.0f;
	static constexpr int width = 33;
	static constexpr int height = 58;
	static constexpr int maxLives = 100;
	static constexpr Color c = Colors::Green;
};