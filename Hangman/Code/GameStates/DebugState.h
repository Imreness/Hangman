#pragma once
#ifndef DEBUGSTATE_CLASS
#define DEBUGSTATE_CLASS
#include "..//Core/GameState.h"


class DebugState : public GameState
{
private:
public:
	virtual void Setup(Resource* res);

	virtual void Update(Resource* res , Camera* cam);

	virtual void Render(Resource* res , Camera* cam);

	virtual void ProcessKeyboard(GLFWwindow* window , Camera* cam , float delta);
};

#endif