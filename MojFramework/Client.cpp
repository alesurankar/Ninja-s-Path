#include "Client.h"

Client::Client()
{
	LoadUsername();
	DeleteUserFile();
}

std::string Client::GetUsername()
{
	return username;
}

bool Client::Exists()
{
	return !username.empty();
}

void Client::LoadUsername()
{
	if (!fs::exists(fullPath)) {
		std::ofstream createFile(fullPath);
		if(createFile.is_open()) {
			createFile << "Offline";
			createFile.close();
		}
	}

	std::ifstream file(fullPath);
	if (file.is_open()) {
		std::getline(file, username);
		file.close();
	}
}

void Client::DeleteUserFile()
{
	std::error_code ec;
	fs::remove(fullPath, ec);
}
