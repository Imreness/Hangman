#pragma once
#ifndef DEBUGSTATE_CLASS
#define DEBUGSTATE_CLASS
#include "..//Core/GameState.h"

class DebugState : public GameState
{
private:

public:
	virtual void Setup();

	virtual void Update();

	virtual void Render();

	virtual void ProcessKeyboard(GLFWwindow* window);
};

#endif