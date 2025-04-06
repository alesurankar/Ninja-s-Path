#pragma once
#include "LivingEntity.h"

class Enemy : public LivingEntity
{
public:
	Enemy(const Vec2& pos_in);
	void Update(GameObject& other, float dt);
	//bool Colliding(Player& player);
	//bool Colliding(Bullet& bul);
	//void Damaged();
private:
	//float inOff = 1.0f;
	//int lives;
	float speed = 80.0f;
	static constexpr int width = 24;
	static constexpr int height = 24;
	//static constexpr int maxLives = Config::enemyLives;
};