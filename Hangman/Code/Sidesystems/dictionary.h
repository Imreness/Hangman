#pragma once
#ifndef DICTIONARY_CLASS
#define DICTIONARY_CLASS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

class Dictionary
{
private:
	std::vector<std::string> m_words;

public:

	Dictionary();

	void LoadNewDictionary(const char* path);

	std::string getRandomWord();
};

#endif