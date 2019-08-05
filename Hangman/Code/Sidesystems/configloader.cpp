#include "configloader.h"

Config ConfigLoader::loadConfig()
{
	Config config;
	config.screenWidth = 896; config.screenHeight = 504; config.useCustomWords = false;

	std::ifstream configFile("config.ini");
	if (configFile.fail())
	{
		std::cout << "WARNING::CONFIG::CONFIG_FILE_NOT_FOUND_GENERATING_NEW\n";
		configFile.close();
		std::ofstream newconfigFile("config.ini");
		newconfigFile << "#resolution - can be low, mid or high\nlow\n";
		config.screenWidth = 896; config.screenHeight = 504;
		newconfigFile << "def";
		config.useCustomWords = false;
		return config;
	}
	else
	{
		std::string line;
		while (std::getline(configFile, line))
		{

			if (line.at(0) == '#')
			{
				continue;
			}

			if (line == "low")
			{
				config.screenWidth = 896; config.screenHeight = 504;
			}
			else if (line == "mid")
			{
				config.screenWidth = 1280; config.screenHeight = 720;
			}
			else if (line == "high")
			{
				config.screenWidth = 1536; config.screenHeight = 864;
			}
			else if (line == "def")
			{
				config.useCustomWords = false;
			}
			else if (line == "cus")
			{
				config.useCustomWords = true;
			}

		}
		return config;
	}
}

void ConfigLoader::SaveConfig(const char* resolution , bool UseCustomWordset)
{
	std::ofstream configFile("config.ini");
	configFile.clear();
	configFile << "#resolution - can be low, mid or high\n" << resolution << "\n";
	if (UseCustomWordset)
		configFile << "cus";
	else
		configFile << "def";
}
