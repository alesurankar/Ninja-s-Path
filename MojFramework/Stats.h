#pragma once
#include <fstream>
#include <string>

class Stats
{
public:
	Stats(std::string filename_in);
	void SaveToFile();
private:
	void LoadFromFile();
public:
	int level;
	int maxHP;
	int maxXP = 1000;
	int power;
	int shield;
	int xp = 100;
	int hp;
	float speed;
private:
	std::string filename;
};