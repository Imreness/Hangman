#pragma once
#ifndef PLAYSTATE_CLASS
#define PLAYSTATE_CLASS
#include "..//Core/GameState.h"
#include <string>
#include <vector>


class PlayState : public GameState
{
private:

	bool m_mouseClicked = false;

	bool m_changeToMenu = false;


	//Session Specific
	int m_lives = 10;

public:

	virtual ~PlayState() {}

	virtual void Setup(GLFWwindow* window, Resource* res, Camera* cam, btDynamicsWorld* physicsWorld);

	virtual STATECHANGE Update(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld, float delta);

	virtual void Render(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld);

	virtual void ProcessKeyboard(GLFWwindow* window, Camera* cam, btDynamicsWorld* physicsWorld, Resource* res, float delta);

};


#endif