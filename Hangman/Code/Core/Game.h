#pragma once
#ifndef GAME_CLASS
#define GAME_CLASS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Physics.h"
#include "Audio.h"

//gamestates
#include "..//GameStates/DebugState.h"
#include "..//GameStates/IntroState.h"
#include "..//GameStates/MenuState.h"
#include "..//GameStates/PlayState.h"

//A master-system handler
class Game
{
private:
	//General
	GLFWwindow* m_window;
	Camera*     m_cam;

	//Other Systems
	GameState*     m_state;
	Resource*      m_res;
	PhysicsEngine* m_physics;
	AudioEngine*   m_audio;

	//Ticks
	//Ticks are used to time render / game logic calls
	double       m_curr_renderTick = 0.0;
	const double m_renderTick = 1.0 / 60.0;

public:
	//Setup the GLFW window, check all the libaries
	Game(Config config, const char* title , GLFWimage* icon);

	void Update();

	void ChangeState(STATECHANGE changeTo);

	bool gameShouldClose() { return glfwWindowShouldClose(m_window); }

	void Close();
};

//Since GLFW is a C libary, it cannot use classes, hence this is outside of the Game class
void mousecallback(GLFWwindow* win, double xpos, double ypos);
#endif