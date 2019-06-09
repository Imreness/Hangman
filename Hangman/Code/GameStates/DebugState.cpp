#include "DebugState.h"

void DebugState::Update(Resource* res , Camera* cam)
{
	cam->Update();
}

void DebugState::ProcessKeyboard(GLFWwindow* window , Camera* cam , float delta)
{
	if (glfwGetKey(window, GLFW_KEY_F9) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cam->Move_DEBUG(CameraMovement_DEBUG::FORWARDS , delta);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cam->Move_DEBUG(CameraMovement_DEBUG::BACKWARDS, delta);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cam->Move_DEBUG(CameraMovement_DEBUG::LEFT, delta);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cam->Move_DEBUG(CameraMovement_DEBUG::RIGHT, delta);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		cam->setSprint_DEBUG(true);
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		cam->setSprint_DEBUG(false);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		cam->setShouldLook_DEBUG(true);
		cam->setCursorLock_DEBUG(window,true);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE)
	{
		cam->setShouldLook_DEBUG(false);
		cam->setFirstMouse_DEBUG(true);
		cam->setCursorLock_DEBUG(window, false);
	}
}

void DebugState::Setup(Resource* res)
{
	res->loadShader("Shaders/object.vert", "Shaders/object.frag", "test");

	res->SpawnObject("homo", "Models/sphere.blend", "test");

	res->SpawnObject("megahomo", "Models/asd.blend", "test");
}

void DebugState::Render(Resource* res , Camera* cam)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	//m_res->getModel("test")->Render(m_res->getShader("test"));
	res->Render(cam->getView() , cam->getProj());
}