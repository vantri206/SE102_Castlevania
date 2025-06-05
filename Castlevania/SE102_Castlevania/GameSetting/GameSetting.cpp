#include "GameSetting.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

std::unordered_map<std::string, float> CGameSettings::settings;

void CGameSettings::LoadFromFile(const std::string& path)
{
	settings.clear();
	std::ifstream file(path);
	std::string line;

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string key;
		float value;

		if (std::getline(iss, key, '=') && iss >> value)
		{
			settings[key] = value;
		}
	}
}

float CGameSettings::Get(const std::string& key, float defaultValue)
{
	auto it = settings.find(key);
	return it != settings.end() ? it->second : defaultValue;
}
