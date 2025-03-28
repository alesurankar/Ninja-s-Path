#include "LivingEntity.h"

LivingEntity::LivingEntity(const Vec2& pos_in, const Vec2& vel_in, float width_in, float height_in, int hp_in, int power_in)
	:
	GameObject(pos_in, vel_in, width_in, height_in),
	hp(hp_in),
	power(power_in),
	destroyed(false)
{}
