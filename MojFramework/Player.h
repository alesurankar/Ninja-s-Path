#pragma once
#include "LivingEntity.h"

class Player : public LivingEntity
{
public:
	Player(const Vec2& pos_in);
	~Player();
	void Draw(Graphics& gfx) const override;
	void DrawXP(Graphics& gfx) const;
	void DrawStatus(Graphics& gfx) const override;
	void Update(const Mouse& mouse, const Keyboard& kbd, float dt);
	bool FiringStatus();
	void Fire();
	void Reload();
	Vec2 GetDirection(const Mouse& mouse); 
private:
	Surface face = Surface("Images\\face36x40.bmp");
	Surface emptyHP = Surface("Images\\Player_bar_empty300x40.bmp");
	Surface fullHP = Surface("Images\\Player_hp_full300x28.bmp");
	Surface fullEnergy = Surface("Images\\Player_energy_full300x12.bmp");
	static constexpr int maxXP = 1000;
	bool firing;
	bool loaded;
	float speed = 100.0f;
	static constexpr int width = 33;
	static constexpr int height = 58;
	static constexpr Color c = Colors::Green;
	float time = 0.0f;
};