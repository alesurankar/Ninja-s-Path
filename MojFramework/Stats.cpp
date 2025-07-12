#include "Stats.h"

Stats::Stats(std::string filename_in)
	:
	filename(std::move(filename_in))
{
	LoadFromFile();
}

void Stats::LoadFromFile()
{
	std::ifstream file(filename);
	if (file)
	{
		file >> maxHP >> hp;
	}
}

void Stats::SaveToFile()
{
	std::ofstream file(filename);
	if (file)
	{
		file << maxHP << " " << hp << "\n";
	}
}
