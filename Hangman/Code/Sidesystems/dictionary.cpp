#include "dictionary.h"
#include <algorithm>

Dictionary::Dictionary()
{

}

void Dictionary::LoadNewDictionary(const char* path)
{
	std::ifstream file(path);

	if (file.fail())
	{
		std::cout << "ERROR::DICTIONARY::CANNOT_LOAD_DICTIONARY_AT: " << path << "\n";
	}
	else
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) {return std::tolower(c); });

			if (line.at(0) == '#')
			{
				continue;
			}
			if (line.length() > 19)
			{
				continue;
			}

			bool shouldContinue = true;
			for (int i = 0; i < line.length(); i++)
			{
				if (line.at(i) == ' ')
				{
					std::cout << "found em spacious motherfuckers tho'\n";
					shouldContinue = false;
				}
				if ((int)line.at(i) < 97 || (int)line.at(i) > 122)
				{
					std::cout << "found em illegal motherfuckers tho'\n";
					shouldContinue = false;
				}
			}

			if (!shouldContinue)
				continue;

			m_words.push_back(line);
		}
	}

}

std::string Dictionary::getRandomWord()
{
	srand(time(NULL));
	if (m_words.size() == 0)
	{
		return std::string("replaceme");
	}
	int number = rand() % m_words.size() + 0;
	return m_words.at(number);
}