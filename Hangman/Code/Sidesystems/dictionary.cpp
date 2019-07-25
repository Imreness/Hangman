#include "dictionary.h"

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
			if (line.at(0) == '#')
			{
				continue;
			}
			else
				m_words.push_back(line);
		}
	}

}

std::string Dictionary::getRandomWord()
{
	srand(time(NULL));
	int number = rand() % m_words.size() + 0;
	return m_words.at(number);
}