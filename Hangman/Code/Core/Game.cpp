#include "Game.h"
#include <iostream>
#include "delta.h"
double mouseXPos = 0, mouseYPos = 0;


Game::Game(const int windowX, const int windowY, const char* title , GLFWimage* icon)
	: m_winX(windowX) , m_winY(windowY)
{
	//Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE       , GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE            , GLFW_FALSE);

	//Create window then check it
	m_window = glfwCreateWindow(m_winX, m_winY, title, NULL, NULL);

	glfwSetWindowIcon(m_window, 1, icon);

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
	glfwSetCursorPosCallback(m_window, mousecallback);

	//Fixes issues with incorrect texture loading
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//Setup the other systems
	m_physics = new PhysicsEngine();
	m_res     = new Resource();
	m_audio   = new AudioEngine();

	m_cam = new Camera(windowX, windowY, glm::vec3(0., 0., 0.));

	//Setup the default game state
	m_state = new IntroState();
	m_state->Setup(m_res,m_cam, m_physics->getWorld());



	DeltaTime::Init();
	m_curr_renderTick = glfwGetTime();
}

void Game::Update()
{
	//Render
	if (m_curr_renderTick <= glfwGetTime())
	{
		//Advance the tick by the specified amount
		m_curr_renderTick += m_renderTick;

		//Calculate Delta time once per every rendered frame
		//AND
		//Update phyiscs


		DeltaTime::CalculateDelta();

		m_physics->Update(m_renderTick);

		//Update Camera and it's values
		m_cam->Mouselook(mouseXPos, mouseYPos);
		m_cam->UpdateMousePos(mouseXPos, mouseYPos);

		m_audio->Update(m_cam->getPos(), m_cam->getFront());

		btDynamicsWorld* physicsWorld = m_physics->getWorld();
		//Process State
		STATECHANGE newstate = m_state->Update(m_res, m_cam, physicsWorld, DeltaTime::deltaTime);

		m_state->ProcessKeyboard(m_window , m_cam, physicsWorld,m_res, DeltaTime::deltaTime);
		m_state->Render(m_res , m_cam , physicsWorld);

		glfwPollEvents();
		glfwSwapBuffers(m_window);


		if (newstate != STATECHANGE::NONE)
		{
			ChangeState(newstate);
		}
	}
}

void Game::ChangeState(STATECHANGE changeTo)
{
	delete m_res;
	m_res = new Resource();

	delete m_state;
	switch (changeTo)
	{
	case STATECHANGE::NONE:
		std::cout << "ERROR::STATECHANGE::CHANGESTATE_CALLED_WITH_NONE_STATE\n";
		break;
	case STATECHANGE::MAINMENU:
		//m_state = new MenuState();
		break;
	default:
		std::cout << "ERROR::STATECHANGE::CHANGESTATE_CALLED_WITH_UNKNOWN_STATE\n";
		break;
	}

	m_state->Setup(m_res, m_cam, m_physics->getWorld());
}

void Game::Close()
{
	//Cleanup
	delete m_state;
	delete m_audio;
	delete m_res;
	delete m_physics;
}

void mousecallback(GLFWwindow* win, double xpos, double ypos)
{
	mouseXPos = xpos; mouseYPos = ypos;
}