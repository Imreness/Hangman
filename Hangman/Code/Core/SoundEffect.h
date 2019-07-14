#ifndef SOUNDEFFECT_CLASS
#define SOUNDEFFECT_CLASS

#include <SFML/Audio.hpp>

class SoundEffect
{
private:
	sf::SoundBuffer m_buffer;
	sf::Sound m_sound;

public:
	SoundEffect(const char* path);

	void Play();
	void Stop();
	//100 = full volume , 0 = silent
	void SetVolume(float amount);
};

#endif