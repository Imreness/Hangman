#pragma once
#ifndef GAMESTATE_CLASS
#define GAMESTATE_CLASS
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Resource.h"
#include "Camera.h"

//A base for all other Gamestates to inherit from
class GameState
{
public:

	virtual ~GameState() {}
	
	virtual void Setup(Resource* res,btDynamicsWorld* physicsWorld) { std::cout << "WARNING::GAMESTATE::SETUP METHOD NOT IMPLEMENTED\n"; }

	virtual void Update(Resource* res , Camera* cam,btDynamicsWorld* physicsWorld) { std::cout << "WARNING::GAMESTATE::UPDATE METHOD NOT IMPLEMENTED\n"; }

	virtual void Render(Resource* res , Camera* cam, btDynamicsWorld* physicsWorld) { std::cout << "WARNING::GAMESTATE::RENDER METHOD NOT IMPLEMENTED\n"; }

	virtual void ProcessKeyboard(GLFWwindow* window , Camera* cam, btDynamicsWorld* physicsWorld, Resource* res, float delta) { std::cout << "WARNING::GAMESTATE::PROCESSKEYBOARD METHOD NOT IMPLEMENTED\n"; }

};

#endif