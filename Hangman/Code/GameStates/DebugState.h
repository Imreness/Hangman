#pragma once
#ifndef DEBUGSTATE_CLASS
#define DEBUGSTATE_CLASS
#include "..//Core/GameState.h"

//TODO - Have render call using the Graphics class
class DebugState : public GameState
{
private:
public:
	virtual void Setup(Resource* res);

	virtual void Update(Resource* res);

	virtual void Render(Resource* res);

	virtual void ProcessKeyboard(GLFWwindow* window);
};

#endif