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
	bool FiringStatus();
	void Fire();
	void Reload();
	void TakeDamage(LivingEntity& other, int weaponBonus);
	int DamageDeal(); 
	int MeleDamage();
	void CollectXP(LivingEntity& other); 
	void LevelUp();
	int GetLevel();
	int GetMaxXP();
	void SaveToFile(std::string filename);
	void ActiveRegenerate(float dt);
	void PasiveRegenerate(float dt);
	void Heal(int amount);
	void Respawn();
protected:
	void ReadDirection(Vec2 dir);
private:
	void LoadFromFile(const std::string& filename);
	virtual void DrawStatus(const Camera& cam, Graphics& gfx) const;
	void Destroyed();
protected:
	int level;
	int maxLives;
	int maxXP = 1000;
	int power;
	int shield;
	int xp = 100;
	int lives;
	float speed;
	bool destroyed;
	Color c;
	bool facingLeft = true;
	std::vector<Animation> animations;
	Sequence curSequence = Sequence::STANDING_RIGHT;
	Fonts bigFont = Fonts("Images\\Fonts16x28.bmp");
	Fonts smallFont = Fonts("Images\\Fonts8x14.bmp");
private:
	std::string filename;
	Surface object;
	bool firing;
	bool loaded;
	float healTime = 0.0f;
};