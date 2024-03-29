#pragma once
#ifndef MENUSTATE_CLASS
#define MENUSTATE_CLASS
#include "..//Core/GameState.h"
#include "..//Sidesystems/configloader.h"

enum class RESOLUTION
{
	LOWRES,
	MIDRES,
	HIGHRES
};

class MenuState : public GameState
{
private:
	//Flags
	bool m_mouseClicked = false;
	bool m_switchToPlay = false;
	bool m_currUseCustomWordset;


	RESOLUTION m_currResolution;

public:

	virtual ~MenuState() {}

	virtual void Setup(GLFWwindow* window, Resource* res, Camera* cam, btDynamicsWorld* physicsWorld);

	virtual STATECHANGE Update(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld, float delta);

	virtual void Render(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld);

	virtual void ProcessKeyboard(GLFWwindow* window, Camera* cam, btDynamicsWorld* physicsWorld, Resource* res, float delta);
};

#endif
