#include "MenuState.h"

void MenuState::Setup(GLFWwindow* window, Resource* res, Camera* cam, btDynamicsWorld* physicsWorld)
{
	res->loadShader("Shaders/object.vert", "Shaders/object.frag", "basicShader");

	m_currUseCustomWordset = res->m_dictionaryUseCustomWords;

	btTransform objectTrans; objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(0, 1.15, 0.));
	res->loadSound("Audio/click.wav");
	res->loadSound("Audio/click_chad.wav");


	//Setup Main Menu
	{
		Texture* logoTexture = res->LoadTexture("Textures/gamelogo.png");
		res->SpawnObject("logo", "Models/banner.assbin", "basicShader", physicsWorld, objectTrans, true, logoTexture)
			->Scale(glm::vec3(0.55, 0.25, 1));

		Texture* optionTexture = res->LoadTexture("Textures/button_options.png");
		objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(-1.5, -0.25, 0.));
		res->SpawnObject("b_options", "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, optionTexture)
			->Scale(glm::vec3(0.5, 0.5, 0.5));

		Texture* loadingTexture = res->LoadTexture("Textures/loading.jpg");
		objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(0., 10, 0.));
		res->SpawnObject("loadingLogo", "Models/banner.assbin", "basicShader", nullptr, objectTrans, true, loadingTexture)
			->Scale(glm::vec3(0.5, 0.5, 0.5));

		Texture* startTexture = res->LoadTexture("Textures/button_start.png");
		objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(0., -0.25, 0.));
		res->SpawnObject("b_startGame", "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, startTexture)
			->Scale(glm::vec3(0.5, 0.5, 0.5));

		Texture* exitTexture = res->LoadTexture("Textures/button_exit.png");
		objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(1.5, -0.25, 0.));
		res->SpawnObject("b_exit", "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, exitTexture)
			->Scale(glm::vec3(0.5, 0.5, 0.5));
	}

	//Option Menu
	{
		res->LoadTexture("Textures/button_lowres.png");
		res->LoadTexture("Textures/button_highres.png");
		res->LoadTexture("Textures/button_midres.png");

		objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(-4, 0.7, 4.)); objectTrans.setRotation(btQuaternion(1.58, 0, 0));
		res->SpawnObject("b_resolution", "Models/button.assbin", "basicShader", physicsWorld, objectTrans)
			->Scale(glm::vec3(0.5, 0.5, 0.5));

		int windowWidth, windowHeight;

		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		if (windowWidth == 896)
		{
			m_currResolution = RESOLUTION::LOWRES;
			res->getObject("b_resolution")->AttachNewOverrideTexture(res->getTexture("button_lowres.png"));
		}
		else if (windowWidth == 1280)
		{
			m_currResolution = RESOLUTION::MIDRES;
			res->getObject("b_resolution")->AttachNewOverrideTexture(res->getTexture("button_midres.png"));
		}
		else
		{
			m_currResolution = RESOLUTION::HIGHRES;
			res->getObject("b_resolution")->AttachNewOverrideTexture(res->getTexture("button_highres.png"));
		}

		res->LoadTexture("Textures/wordset_def.jpg");
		res->LoadTexture("Textures/wordset_cus.jpg");

		Texture* wordsetTexture;
		if (res->m_dictionaryUseCustomWords)
			wordsetTexture = res->getTexture("wordset_cus.jpg");
		else
			wordsetTexture = res->getTexture("wordset_def.jpg");

		objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(-4, -0.7, 4.5)); objectTrans.setRotation(btQuaternion(1.58, 0, 0));
		res->SpawnObject("wordsetLogo", "Models/banner.assbin", "basicShader", nullptr, objectTrans, true, wordsetTexture)
			->Scale(glm::vec3(0.2, 0.2, 0.2));

		Texture* changwordsetTexture = res->LoadTexture("Textures/button_change.png");
		objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(-4, -0.7, 3.23)); objectTrans.setRotation(btQuaternion(1.58, 0, 0));
		res->SpawnObject("b_changewordset", "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, changwordsetTexture)
			->Scale(glm::vec3(0.5, 0.5, 0.5));

		Texture* lowerresTexture = res->LoadTexture("Textures/button_left.png");
		objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(-4, 0.7, 5)); objectTrans.setRotation(btQuaternion(1.58, 0, 0));
		res->SpawnObject("b_lowerres", "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, lowerresTexture)
			->Scale(glm::vec3(0.25, 0.5, 0.5));

		objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(-4, -1.9, 5.9)); objectTrans.setRotation(btQuaternion(1.58, 0, 0));
		res->SpawnObject("b_chad", "Models/button.assbin", "basicShader", physicsWorld, objectTrans)
			->Scale(glm::vec3(0.2, 0.2, 0.2));
		res->getObject("b_chad")->setShouldRender(false);

		Texture* higherresTexture = res->LoadTexture("Textures/button_right.png");
		objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(-4, 0.7, 3)); objectTrans.setRotation(btQuaternion(1.58, 0, 0));
		res->SpawnObject("b_higherres", "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, higherresTexture)
			->Scale(glm::vec3(0.25, 0.5, 0.5));

		Texture* applyresTexture = res->LoadTexture("Textures/button_apply.png");
		objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(-4, 0.7, 2)); objectTrans.setRotation(btQuaternion(1.58, 0, 0));
		res->SpawnObject("b_applyres", "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, applyresTexture)
			->Scale(glm::vec3(0.5, 0.5, 0.5));

		Texture* backoptionsTexture = res->LoadTexture("Textures/button_back.png");
		objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(-4, -0.7, 2)); objectTrans.setRotation(btQuaternion(1.58, 0, 0));
		res->SpawnObject("b_backoptions", "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, backoptionsTexture)
			->Scale(glm::vec3(0.5, 0.5, 0.5)); 
	}
	
	cam->SetTransform(glm::vec3(0., 0., 3.), -90., 0.);
}

STATECHANGE MenuState::Update(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld, float delta)
{
	cam->Update(delta);

	if (m_switchToPlay)
		return STATECHANGE::PLAY;
	else
		return STATECHANGE::NONE;
}

void MenuState::Render(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.f, 1.0f);

	res->Render(cam->getView(), cam->getProj());
}

void MenuState::ProcessKeyboard(GLFWwindow* window, Camera* cam, btDynamicsWorld* physicsWorld, Resource* res, float delta)
{
	if (glfwGetMouseButton(window, 0) == GLFW_RELEASE)
		m_mouseClicked = false;

	if (glfwGetMouseButton(window, 0) == GLFW_PRESS && !m_mouseClicked)
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
			if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_exit")
			{
				res->getSound("click.wav")->Play();
				glfwSetWindowShouldClose(window, true);
			}
			else if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_startGame")
			{
				res->getSound("click.wav")->Play();
				cam->SetTransform(glm::vec3(0., 10., 3.), -90., 0.);
				cam->SetTargetPos_rail(glm::vec3(0., 10., 3.), -90., 0.);
				m_switchToPlay = true;
			}
			else if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_options")
			{
				res->getSound("click.wav")->Play();
				cam->SetTargetPos_rail(glm::vec3(-1, 0., 3), -180., 0.);
			}
			else if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_backoptions")
			{
				res->getSound("click.wav")->Play();
				cam->SetTargetPos_rail(glm::vec3(0, 0., 3), -90., 0.);
			}
			else if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_chad")
			{
				res->getSound("click_chad.wav")->Play();
				res->m_useChadWarden = true;
			}

			else if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_changewordset")
			{
				res->getSound("click.wav")->Play();
				if (m_currUseCustomWordset)
				{
					m_currUseCustomWordset = false;
					res->getObject("wordsetLogo")->AttachNewOverrideTexture(res->getTexture("wordset_def.jpg"));
				}
				else
				{
					m_currUseCustomWordset = true;
					res->getObject("wordsetLogo")->AttachNewOverrideTexture(res->getTexture("wordset_cus.jpg"));
				}

				res->m_dictionaryUseCustomWords = m_currUseCustomWordset;

				switch (m_currResolution)
				{
				case RESOLUTION::LOWRES:
					glfwSetWindowSize(window, 896, 504);
					glViewport(0, 0, 896, 504);
					cam->RecalculateProjection(896, 504);
					ConfigLoader::SaveConfig("low", m_currUseCustomWordset);
					break;
				case RESOLUTION::MIDRES:
					glfwSetWindowSize(window, 1280, 720);
					glViewport(0, 0, 1280, 720);
					cam->RecalculateProjection(1280, 720);
					ConfigLoader::SaveConfig("mid", m_currUseCustomWordset);
					break;
				case RESOLUTION::HIGHRES:
					glfwSetWindowSize(window, 1536, 864);
					glViewport(0, 0, 1536, 864);
					cam->RecalculateProjection(1536, 864);
					ConfigLoader::SaveConfig("high", m_currUseCustomWordset);
					break;
				default:
					break;
				}

			}

			else if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_higherres")
			{
				res->getSound("click.wav")->Play();
				switch (m_currResolution)
				{
				case RESOLUTION::LOWRES:
					m_currResolution = RESOLUTION::MIDRES;
					res->getObject("b_resolution")->AttachNewOverrideTexture(res->getTexture("button_midres.png"));
					break;
				case RESOLUTION::MIDRES:
					m_currResolution = RESOLUTION::HIGHRES;
					res->getObject("b_resolution")->AttachNewOverrideTexture(res->getTexture("button_highres.png"));
					break;
				case RESOLUTION::HIGHRES:
					m_currResolution = RESOLUTION::LOWRES;
					res->getObject("b_resolution")->AttachNewOverrideTexture(res->getTexture("button_lowres.png"));
					break;
				default:
					break;
				}
			}
			else if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_lowerres")
			{
				res->getSound("click.wav")->Play();
				switch (m_currResolution)
				{
				case RESOLUTION::LOWRES:
					m_currResolution = RESOLUTION::HIGHRES;
					res->getObject("b_resolution")->AttachNewOverrideTexture(res->getTexture("button_highres.png"));
					break;
				case RESOLUTION::MIDRES:
					m_currResolution = RESOLUTION::LOWRES;
					res->getObject("b_resolution")->AttachNewOverrideTexture(res->getTexture("button_lowres.png"));
					break;
				case RESOLUTION::HIGHRES:
					m_currResolution = RESOLUTION::MIDRES;
					res->getObject("b_resolution")->AttachNewOverrideTexture(res->getTexture("button_midres.png"));
					break;
				default:
					break;
				}
			}

			else if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_applyres")
			{
				res->getSound("click.wav")->Play();
				switch (m_currResolution)
				{
				case RESOLUTION::LOWRES:
					glfwSetWindowSize(window, 896, 504);
					glViewport(0, 0, 896, 504);
					cam->RecalculateProjection(896, 504);
					ConfigLoader::SaveConfig("low", m_currUseCustomWordset);
					break;
				case RESOLUTION::MIDRES:
					glfwSetWindowSize(window, 1280, 720);
					glViewport(0, 0, 1280, 720);
					cam->RecalculateProjection(1280, 720);
					ConfigLoader::SaveConfig("mid", m_currUseCustomWordset);
					break;
				case RESOLUTION::HIGHRES:
					glfwSetWindowSize(window, 1536, 864);
					glViewport(0, 0, 1536, 864);
					cam->RecalculateProjection(1536, 864);
					ConfigLoader::SaveConfig("high", m_currUseCustomWordset);
					break;
				default:
					break;
				}
			}

		}

	}

	//Camera Input
	//{
	//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	{
	//		cam->Move_DEBUG(CameraMovement_DEBUG::FORWARDS, delta);
	//	}
	//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//	{
	//		cam->Move_DEBUG(CameraMovement_DEBUG::BACKWARDS, delta);
	//	}
	//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//	{
	//		cam->Move_DEBUG(CameraMovement_DEBUG::LEFT, delta);
	//	}
	//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//	{
	//		cam->Move_DEBUG(CameraMovement_DEBUG::RIGHT, delta);
	//	}
	//	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	//	{
	//		cam->setSprint_DEBUG(true);
	//	}
	//	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	//	{
	//		cam->setSprint_DEBUG(false);
	//	}
	//	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	//	{
	//		if (cam->getMode() == CameraMode::DEBUG)
	//		{
	//			cam->setShouldLook_DEBUG(true);
	//			cam->setCursorLock_DEBUG(window, true);
	//		}
	//	}
	//	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE)
	//	{
	//		if (cam->getMode() == CameraMode::DEBUG)
	//		{
	//			cam->setShouldLook_DEBUG(false);
	//			cam->setFirstMouse_DEBUG(true);
	//			cam->setCursorLock_DEBUG(window, false);
	//		}
	//	}

	//	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
	//	{
	//		cam->SetMode(CameraMode::ONRAILS);
	//	}
	//	if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
	//	{
	//		cam->SetMode(CameraMode::DEBUG);
	//	}

	//}
}