#ifndef AUDIO_CLASS
#define AUDIO_CLASS
#include <SFML/Audio.hpp>
#include <glm/glm.hpp>

class AudioEngine
{
private:
	void setListenerPosition(glm::vec3 position);
	void setListenerDirection(glm::vec3 direction);
public:

	AudioEngine();

	void Update(glm::vec3 camPosition, glm::vec3 camFront);
};

#endif