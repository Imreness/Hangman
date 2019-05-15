#include "Game.h"
#include <iostream>

Game::Game(const int windowX, const int windowY, const char title)
	: m_winX(windowX) , m_winY(windowY)
{
	//Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//Create window then check it
	m_window = glfwCreateWindow(m_winX, m_winY, &title, NULL, NULL);

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

	
}

void Game::Update()
{
	//TODO - Use Render Call instead

}