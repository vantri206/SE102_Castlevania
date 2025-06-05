#pragma once

#include <unordered_map>
#include <string>

class CGameSettings
{
	static std::unordered_map<std::string, float> settings;
public:
	static void LoadFromFile(const std::string& path);
	static float Get(const std::string& key, float defaultValue = 0.0f);
};
