#pragma once
#ifndef DEBUGSTATE_CLASS
#define DEBUGSTATE_CLASS
#include "..//Core/GameState.h"

class DebugState : public GameState
{
private:
	bool m_mouseClicked;
public:
	virtual void Setup(Resource* res, btDynamicsWorld* physicsWorld);

	void Update(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld, float delta);

	virtual void Render(Resource* res , Camera* cam, btDynamicsWorld* physicsWorld);

	virtual void ProcessKeyboard(GLFWwindow* window , Camera* cam, btDynamicsWorld* physicsWorld, Resource* res, float delta);
};

#endif