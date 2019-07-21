#pragma once
#ifndef CONFIGLOADER_CLASS
#define CONFIGLOADER_CLASS
#include <iostream>
#include <fstream>
#include <string>

struct Config
{
	int screenWidth;
	int screenHeight;
};

static class ConfigLoader
{
public:
	static Config loadConfig();
	static void SaveConfig(const char* resolution);
};

#endif