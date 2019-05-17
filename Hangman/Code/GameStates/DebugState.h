#pragma once
#ifndef DEBUGSTATE_CLASS
#define DEBUGSTATE_CLASS
#include "..//Core/GameState.h"
#include "..//Core/Resource.h"

class DebugState : public GameState
{
private:
	Model* m_model;
	Resource* m_res;
public:
	virtual void Setup();

	virtual void Update();

	virtual void Render();

	virtual void ProcessKeyboard(GLFWwindow* window);
};

#endif