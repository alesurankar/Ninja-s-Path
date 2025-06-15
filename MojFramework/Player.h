#pragma once
#include "LivingEntity.h"
#include "Fonts.h"

class Player : public LivingEntity
{
public:
	Player(const Vec2& pos_in);
	void DrawStatus(Graphics& gfx) const override;
	void Update(const Mouse& mouse, const Keyboard& kbd, float dt);
	bool FiringStatus();
	void Fire();
	void Reload();
	Vec2 GetDirection(const Mouse& mouse); 
	void Heal(float dt) override;
private:
	Surface face = Surface("Images\\face36x40.bmp");
	bool firing;
	bool loaded;
	float speed = 100.0f;
	static constexpr int width = 33;
	static constexpr int height = 58;
	static constexpr Color c = Colors::Green;
	Fonts bigFont = Fonts("Images\\Fonts16x28.bmp");
	Fonts smallFont = Fonts("Images\\Fonts8x14.bmp");
	float time = 0.0f;
};