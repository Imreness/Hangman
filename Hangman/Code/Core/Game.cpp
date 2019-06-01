#include "Game.h"
#include <iostream>
#include "delta.h"

Game::Game(const int windowX, const int windowY, const char* title)
	: m_winX(windowX) , m_winY(windowY)
{
	//Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//Create window then check it
	m_window = glfwCreateWindow(m_winX, m_winY, title, NULL, NULL);

	if (!m_window)
	{
		std::cout << "ERROR::CORE::GLFW - FAILED TO CREATE WINDOW\n";
	}

	//Make it the current OpenGL context
	glfwMakeContextCurrent(m_window);

	//See if GLAD is loaded successfully
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR::CORE::GLAD - FAILED TO LOAD\n";
	}

	//Make depth testing enabled, enabling us to do 3D
	glEnable(GL_DEPTH_TEST);

	//Set other values
	glViewport(0, 0, m_winX, m_winY);

	m_res = new Resource();

	//Setup the default game state
	m_state = new DebugState();
	m_state->Setup(m_res);
	
}

void Game::Update()
{
	//Render
	if (m_curr_renderTick <= glfwGetTime())
	{
		//Advance the tick by the specified amount
		m_curr_renderTick += m_renderTick;
		//Calculate Delta time once per every rendered frame
		DeltaTime::CalculateDelta();

		m_state->Update(m_res);
		m_state->ProcessKeyboard(m_window);
		m_state->Render(m_res);

		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}
}

void Game::Close()
{
	delete m_res;
}