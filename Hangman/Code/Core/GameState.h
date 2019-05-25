#pragma once
#ifndef GAMESTATE_CLASS
#define GAMESTATE_CLASS
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Resource.h"

class GameState
{
public:

	virtual ~GameState() {}
	
	virtual void Setup(Resource* res) { std::cout << "WARNING::GAMESTATE::SETUP METHOD NOT IMPLEMENTED\n"; }

	virtual void Update(Resource* res) { std::cout << "WARNING::GAMESTATE::UPDATE METHOD NOT IMPLEMENTED\n"; }

	virtual void Render(Resource* res) { std::cout << "WARNING::GAMESTATE::RENDER METHOD NOT IMPLEMENTED\n"; }

	virtual void ProcessKeyboard(GLFWwindow* window) { std::cout << "WARNING::GAMESTATE::PROCESSKEYBOARD METHOD NOT IMPLEMENTED\n"; }

};

#endif