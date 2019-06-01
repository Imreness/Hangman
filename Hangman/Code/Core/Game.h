#pragma once
#ifndef GAME_CLASS
#define GAME_CLASS
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Default gamestate
#include "..//GameStates/DebugState.h"

class Game
{
private:
	//General
	GLFWwindow* m_window;
	const int   m_winX, m_winY;

	//Other Systems
	GameState* m_state;
	Resource* m_res;

	//Ticks
	//Ticks are used to time render / game logic calls
	double       m_curr_renderTick = 0.0;
	const double m_renderTick = 1.0 / 60.0;


public:
	//Setup the GLFW window, check all the libaries
	Game(const int windowX , const int windowY , const char* title);

	void Update();

	bool gameShouldClose() { return glfwWindowShouldClose(m_window); }

	void Close();
};

#endif