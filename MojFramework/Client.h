#pragma once
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class Client
{
public:
	Client();
	std::string GetUsername();
	bool Exists();
private:
	void LoadUsername();
	void DeleteUserFile();
private:
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string usernamePath = "/username.txt";
	std::string fullPath = parentDir + usernamePath;
	std::string username;
};