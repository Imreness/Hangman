#include "DebugState.h"

void DebugState::Update(Resource* res , Camera* cam, btDynamicsWorld* physicsWorld , float delta)
{
	cam->Update(delta);
}


void DebugState::Setup(Resource* res, btDynamicsWorld* physicsWorld)
{
	res->loadShader("Shaders/object.vert", "Shaders/object.frag", "test");


	//btTransform box1Trans;
	//box1Trans.setIdentity();
	//res->SpawnObject("homo", "Models/cube.blend", "test", physicsWorld, box1Trans);

	res->LoadTexture("Textures/button_oldman.png");
	res->LoadTexture("Textures/boxtemplate.png");

	res->SpawnObject("mainbox", "Models/button.blend", "test", physicsWorld, btTransform::getIdentity(),
						true , res->getTexture("boxtemplate.png"));

	btTransform sideboxTransform; sideboxTransform.setIdentity();
	sideboxTransform.setOrigin(btVector3(0. , 5. , 0.));
	res->SpawnObject("sidebox", "Models/button.blend", "test", physicsWorld, sideboxTransform,
						true, res->getTexture("button_oldman.png"));

	//Physics Debug objects
	//res->SpawnObject("guide1", "Models/asd.blend", "test", physicsWorld);
	//res->SpawnObject("guide2", "Models/asd.blend", "test", physicsWorld);
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
		if (cam->getMode() == CameraMode::DEBUG)
		{
			cam->setShouldLook_DEBUG(true);
			cam->setCursorLock_DEBUG(window, true);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE)
	{
		if (cam->getMode() == CameraMode::DEBUG)
		{
			cam->setShouldLook_DEBUG(false);
			cam->setFirstMouse_DEBUG(true);
			cam->setCursorLock_DEBUG(window, false);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
	{
		cam->SetMode(CameraMode::ONRAILS);
	}
	if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
	{
		cam->SetMode(CameraMode::DEBUG);
	}

	if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
	{
		cam->SetTargetPos_rail(glm::vec3(0., 0., 3.), -90.f, 0.f);
	}
	if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
	{
		cam->SetTargetPos_rail(glm::vec3(0., 5., 3.), -90.f, 0.f);
	}



	//Raycast
	if (glfwGetMouseButton(window , 0) == GLFW_PRESS)
	{
		Mouse3DPosition MousePos = cam->getMouse3DPositions(window);

		glm::vec3 startPos = MousePos.StartPos;
		glm::vec3 endPos = startPos + MousePos.Direction * 100.f;

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

void DebugState::Render(Resource* res , Camera* cam, btDynamicsWorld* physicsWorld)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.f, 1.0f);

	res->Render(cam->getView() , cam->getProj());
}