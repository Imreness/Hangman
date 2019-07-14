#pragma once
#ifndef MUSIC_CLASS
#define MUSIC_CLASS
#include <SFML/Audio.hpp>

class Music
{
private:
	sf::Music m_music;
public:
	Music(const char* path);

	void Play();
	void Stop();
	//100 - full volume , 0 - silent
	void setVolume(float amount);
};

#endif