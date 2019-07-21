#include "configloader.h"

Config ConfigLoader::loadConfig()
{
	Config config;

	std::ifstream configFile("config.ini");
	if (configFile.fail())
	{
		std::cout << "WARNING::CONFIG::CONFIG_FILE_NOT_FOUND_GENERATING_NEW\n";
		configFile.close();
		std::ofstream newconfigFile("config.ini");
		newconfigFile << "#resolution - can be low, mid or high\nlow";
		config.screenWidth = 896; config.screenHeight = 504;
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
				return config;
			}
			else if (line == "mid")
			{
				config.screenWidth = 1280; config.screenHeight = 720;
				return config;
			}
			else if (line == "high")
			{
				config.screenWidth = 1536; config.screenHeight = 864;
				return config;
			}
		}

		std::cout << "ERROR::CONFIG::CANNOT_FIND_RESOLUTION_IN_CONFIG\n";
	}
}

void ConfigLoader::SaveConfig(const char* resolution)
{
	std::ofstream configFile("config.ini");
	configFile.clear();
	configFile << "#resolution - can be low, mid or high\n" << resolution;
}
