#include "SoundEffect.h"
#include <iostream>

SoundEffect::SoundEffect(const char* path)
{
	if (!m_buffer.loadFromFile(path))
		std::cout << "ERROR::AUDIO::SOUNDEFFECT::FAILED_TO_LOAD_FILE\n @ " << path << "\n";

	m_sound.setBuffer(m_buffer);
}

SoundEffect::~SoundEffect()
{
	m_sound.stop();
}

void SoundEffect::Play()
{
	m_sound.play();
}

void SoundEffect::Stop()
{
	m_sound.stop();
}

void SoundEffect::SetVolume(float amount)
{
	m_sound.setVolume(amount);
}
