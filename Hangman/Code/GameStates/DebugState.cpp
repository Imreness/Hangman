#include "DebugState.h"

void DebugState::Update(Resource* res , Camera* cam, btDynamicsWorld* physicsWorld , float delta)
{
	cam->Update();
}


void DebugState::ProcessKeyboard(GLFWwindow* window , Camera* cam, btDynamicsWorld* physicsWorld, Resource* res, float delta)
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


	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		res->getObject("homo")->Translate(glm::vec3(0.0, 3 * delta, 0.0));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		res->getObject("homo")->Translate(glm::vec3(0.0, -3 * delta, 0.0));
	}

	if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
	{
		res->getObject("homo")->Scale(glm::vec3(0.01, 0.01, 0.01), false);
	}
	if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
	{
		res->getObject("homo")->Scale(-glm::vec3(0.01, 0.01, 0.01), false);
	}

	if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
	{
		res->getObject("homo")->Rotate(0, 0.1, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
	{
		res->getObject("homo")->Rotate(0, -0.1, 0);
	}


	//Raycast
	if (glfwGetMouseButton(window , 0) == GLFW_PRESS)
	{
		int windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		//std::cout << "Mouse pos: " << cam->getMouseX_OVERALL() << " " << cam->getMouseY_OVERALL() << "\n" <<
		//	"Window Size: " << windowWidth << " " << windowHeight << "\n";

		//Raycast
		glm::vec4 RayStart_NDC(
			((float)cam->getMouseX_OVERALL() / windowWidth - 0.5f) * 2.0f,
			(((float)cam->getMouseY_OVERALL() / windowHeight - 0.5f) * 2.0f) * -1.f,
			-1.0f,
			1.0f
		);

		glm::vec4 RayEnd_NDC(
			((float)cam->getMouseX_OVERALL() / windowWidth - 0.5f) * 2.0f,
			(((float)cam->getMouseY_OVERALL() / windowHeight - 0.5f) * 2.0f) * -1.f,
			0.0f,
			1.0f
		);


		glm::mat4 M = glm::inverse(cam->getProj() * cam->getView());

		glm::vec4 RayStart_world = M * RayStart_NDC; RayStart_world /= RayStart_world.w;
		glm::vec4 RayEnd_world = M * RayEnd_NDC; RayEnd_world /= RayEnd_world.w;

		glm::vec3 Raydir_world(RayEnd_world - RayStart_world);

		Raydir_world = glm::normalize(Raydir_world);

		glm::vec3 startPos = RayStart_world;
		glm::vec3 endPos = startPos + Raydir_world * 100.f;

		btCollisionWorld::AllHitsRayResultCallback rayCallback(
			btVector3(startPos.x, startPos.y, startPos.z),
			btVector3(endPos.x, endPos.y, endPos.z)
		);

		physicsWorld->rayTest(
			btVector3(startPos.x, startPos.y, startPos.z),
			btVector3(endPos.x, endPos.y, endPos.z),
			rayCallback
		);

		if (rayCallback.hasHit())
		{
			std::cout << ((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() << "\n";;
			//res->getObject("guide2")->Translate(glm::vec3(rayCallback.m_hitPointWorld[0].x(),
			//	rayCallback.m_hitPointWorld[0].y(),
			//	rayCallback.m_hitPointWorld[0].z()));
		}

		//res->getObject("guide1")->Translate(startPos, true);

	}
}

void DebugState::Setup(Resource* res, btDynamicsWorld* physicsWorld)
{
	res->loadShader("Shaders/object.vert", "Shaders/object.frag", "test");

	res->SpawnObject("homo", "Models/cube.blend", "test", physicsWorld);
	//res->SpawnObject("guide1", "Models/asd.blend", "test", physicsWorld);
	//res->SpawnObject("guide2", "Models/asd.blend", "test", physicsWorld);
}

void DebugState::Render(Resource* res , Camera* cam, btDynamicsWorld* physicsWorld)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	//m_res->getModel("test")->Render(m_res->getShader("test"));
	res->Render(cam->getView() , cam->getProj());
}