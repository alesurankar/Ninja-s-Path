#pragma once
#include "LivingEntity.h"
#include "Player.h"
#include "Bullet.h"

class Enemy// : LivingEntity
{
public:
	Enemy(const Vec2& pos_in, const Vec2& vel_in);
	void BorderCheck();
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	bool Colliding(Player& player);
	bool Colliding(Bullet& bul);
	bool DestroyedStatus();
	void Damaged();
	Vec2 GetPos();
private:
	Surface s = Surface("Images\\SpriteEnemy24x24.bmp");
	float inOff = 1.0f;
	int lives;
	bool destroyed;
	Vec2 pos;
	Vec2 vel;
	static constexpr float width = 24.0f;
	static constexpr float height = 24.0f;
	static constexpr int maxLives = Config::enemyLives;
};