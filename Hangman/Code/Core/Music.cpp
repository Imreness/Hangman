#include "Music.h"
#include <iostream>

Music::Music(const char* path)
{
	if (!m_music.openFromFile(path))
		std::cout << "ERROR::AUDIO::MUSIC::FAILED_TO_LOAD_FILE @" << path << "\n";
	m_music.setLoop(true);
}

void Music::Play()
{
	m_music.play();
}

void Music::Stop()
{
	m_music.stop();
}

void Music::setVolume(float amount)
{
	m_music.setVolume(amount);
}

