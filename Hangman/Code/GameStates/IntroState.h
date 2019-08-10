#pragma once
#ifndef INTRO_GAMESTATE_CLASS
#define INTRO_GAMESTATE_CLASS
#include "..//Core/GameState.h"

class IntroState : public GameState
{
private:

	//Animation flags
	bool m_switchToMenu = false;
	bool m_showedMadeby = false;
	bool m_showedLogo = false;
	bool m_playedFirstSound = false;

	float m_animationSpeed = 1.f;
	float m_animationLength = 1.f;

	double m_animationTimer = 0.;

public:
	virtual ~IntroState() {}

	virtual void Setup(GLFWwindow* window ,Resource* res, Camera* cam, btDynamicsWorld* physicsWorld);

	virtual STATECHANGE Update(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld, float delta);

	virtual void Render(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld);

	virtual void ProcessKeyboard(GLFWwindow* window, Camera* cam, btDynamicsWorld* physicsWorld, Resource* res, float delta);

};

#endif