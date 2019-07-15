#include "DebugState.h"

void DebugState::Update(Resource* res , Camera* cam, btDynamicsWorld* physicsWorld , float delta)
{
	cam->Update(delta);
}


void DebugState::Setup(Resource* res, btDynamicsWorld* physicsWorld)
{
	res->loadShader("Shaders/object.vert", "Shaders/object.frag", "test");

	res->LoadTexture("Textures/windmillAtlas.png");


	btTransform lowerButtonTrans; lowerButtonTrans.setIdentity();
	res->SpawnObject("lowerButton", "Models/button.blend", "test", physicsWorld, lowerButtonTrans);

	btTransform upperButtonTrans; upperButtonTrans.setIdentity();
	upperButtonTrans.setOrigin(btVector3(5., 0., 0.));
	res->SpawnObject("upperButton", "Models/button.blend", "test", physicsWorld, upperButtonTrans, true , res->getTexture("windmillAtlas.png"));
}


void DebugState::ProcessKeyboard(GLFWwindow* window, Camera* cam, btDynamicsWorld* physicsWorld, Resource* res, float delta)
{
	if (glfwGetKey(window, GLFW_KEY_F9) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	//Camera Input
	{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cam->Move_DEBUG(CameraMovement_DEBUG::FORWARDS, delta);
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

	}

	if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
	{
		cam->SetTargetPos_rail(glm::vec3(0., 0., 3.), -90.f, 0.f);
	}
	if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
	{
		cam->SetTargetPos_rail(glm::vec3(5., 0., 3.), -90.f, 0.f);
	}



	//Raycast
	if (glfwGetMouseButton(window , 0) == GLFW_PRESS && !m_mouseClicked)
	{
		m_mouseClicked = true;
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

	if (glfwGetMouseButton(window, 0) == GLFW_RELEASE)
		m_mouseClicked = false;
}

void DebugState::Render(Resource* res , Camera* cam, btDynamicsWorld* physicsWorld)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.f, 1.0f);

	res->Render(cam->getView() , cam->getProj());
}