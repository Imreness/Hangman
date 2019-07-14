#include "Audio.h"
#include <iostream>

AudioEngine::AudioEngine()
{
}

void AudioEngine::Update(glm::vec3 camPosition, glm::vec3 camFront)
{
	setListenerPosition(camPosition);
	setListenerDirection(camFront - camPosition);
}

void AudioEngine::setListenerPosition(glm::vec3 position)
{
	sf::Listener::setPosition(sf::Vector3(position.x, position.y, position.z));
}
void AudioEngine::setListenerDirection(glm::vec3 direction)
{
	sf::Listener::setDirection(sf::Vector3(direction.x , direction.y , direction.z));
}
