#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Fonts.h"
#include <vector>

class LivingEntity : public GameObject
{
public:
	enum class Sequence
	{
		STANDING_RIGHT,
		STANDING_LEFT,
		WALKING_RIGHT,
		WALKING_LEFT
	};
	LivingEntity(const Vec2& pos_in, const Surface& object_in, int width_in, int height_in, const std::string& filename_in, Color c_in);
	void Draw(const Camera& cam, Graphics& gfx) const override;
	bool DestroyedStatus();
	void Damaged();
	void SaveToFile(std::string filename);
	void ActiveRegenerate(float dt);
	void PasiveRegenerate(float dt);
	void Heal(int amount);
	void Respawn();
private:
	virtual void DrawStatus(const Camera& cam, Graphics& gfx) const;
	void LoadFromFile(const std::string& filename);
	void Destroyed();
protected:
	void ReadDirection(Vec2 dir);
protected:
	bool destroyed;
	int maxLives;
	int lives;
	int maxXP;
	int xp = 100;
	float speed;
	Color c;
	std::vector<Animation> animations;
	Sequence curSequence = Sequence::STANDING_RIGHT;
	bool facingLeft = true;
	Fonts bigFont = Fonts("Images\\Fonts16x28.bmp");
	Fonts smallFont = Fonts("Images\\Fonts8x14.bmp");
private:
	std::string filename;
	Surface object;
	float healTime = 0.0f;
};