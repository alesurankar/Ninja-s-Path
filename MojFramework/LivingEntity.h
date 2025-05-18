#pragma once
#include "GameObject.h"
#include "Animation.h"
#include <vector>

class LivingEntity : public GameObject
{
public:
	enum class Sequence
	{
		STANDING_RIGHT,
		STANDING_LEFT,
		WALKING_RIGHT,
		WALKING_LEFT,
		COUNT
	};
	LivingEntity(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in, const std::string& filename_in, Color c_in);
	void Draw(Graphics& gfx) const override;
	virtual void DrawStatus(Graphics& gfx) const;
	bool DestroyedStatus();
	void Damaged();
	void SaveToFile(std::string filename);
	virtual void Heal(float dt) = 0;
private:
	void LoadFromFile(const std::string& filename);
	void Destroyed();
protected:
	void ReadDirection(Vec2 dir);
protected:
	std::string filename;
	Surface object;
	bool destroyed;
	float inOff = 1.0f;
	int maxLives;
	int lives;
	float speed;
	Color c;
	std::vector<Animation> animations;
	Sequence curSequence = Sequence::STANDING_RIGHT;
	bool facingLeft = true;
};