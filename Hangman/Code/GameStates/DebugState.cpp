#include "DebugState.h"

void DebugState::Update(Resource* res)
{
}

void DebugState::ProcessKeyboard(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void DebugState::Setup(Resource* res)
{
	res->SpawnObject("debug", "Models/asd.blend");
	res->SpawnObject("debug2", "Models/asd.blend");
	res->loadShader("Shaders/object.vert", "Shaders/object.frag" , "test");
}

void DebugState::Render(Resource* res)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	//m_res->getModel("test")->Render(m_res->getShader("test"));
	res->getObject("debug")->Render(res->getShader("test"));
	res->getObject("debug2")->Render(res->getShader("test"));
}