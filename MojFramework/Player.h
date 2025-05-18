#pragma once
#include "LivingEntity.h"

class Player : public LivingEntity
{
public:
	Player(const Vec2& pos_in); 
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
	bool firing;
	bool loaded; 
	static constexpr float moveSlow = 100.0f;
	static constexpr float moveFast = 200.0f;
	static constexpr int width = 33;
	static constexpr int height = 58;
	static constexpr Color c = Colors::Green;
};