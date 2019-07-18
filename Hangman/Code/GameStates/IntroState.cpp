#include "IntroState.h"
#include <iostream>

void IntroState::Setup(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld)
{
	res->loadShader("Shaders/object.vert", "Shaders/object.frag", "basicShader");

	Texture* logoTexture = res->LoadTexture("Textures/logo.jpg");
	btTransform logoTrans; logoTrans.setIdentity(); logoTrans.setOrigin(btVector3(10., 0., 0.));
	res->SpawnObject("logo", "Models/banner.blend", "basicShader", physicsWorld, logoTrans, true, logoTexture);

	Texture* madebyTexture = res->LoadTexture("Textures/madeby.jpg");
	btTransform madebyTrans; madebyTrans.setIdentity();
	res->SpawnObject("madeby", "Models/banner.blend", "basicShader", physicsWorld, madebyTrans, true, madebyTexture);

	res->loadSound("Audio/swoosh1.wav");
	res->loadSound("Audio/swoosh2.wav");
	res->loadSound("Audio/swoosh3.wav");

	cam->SetTransform(glm::vec3(-10., 0., 3.), -90., 0.);
	cam->SetTargetPos_rail(glm::vec3(0., 0., 3.), -90., 0., m_animationSpeed);
}

STATECHANGE IntroState::Update(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld, float delta)
{
	cam->Update(delta);

	if (!m_playedFirstSound)
	{
		res->getSound("swoosh1.wav")->Play();
		m_playedFirstSound = true;
	}


	m_animationTimer += delta;

	if (!m_showedMadeby)
	{
		if (m_animationTimer >= m_animationLength)
		{
			m_showedMadeby = true;
			m_animationTimer = 0.;
			cam->SetTargetPos_rail(glm::vec3(10., 0., 3.), -90., 0., m_animationSpeed);
			res->getSound("swoosh2.wav")->Play();
			return STATECHANGE::NONE;
		}
		return STATECHANGE::NONE;
	}

	if (!m_showedLogo)
	{
		if (m_animationTimer >= m_animationLength)
		{
			m_showedLogo = true;
			m_animationTimer = 0.;
			cam->SetTargetPos_rail(glm::vec3(20., 0., 3.), -90., 0., m_animationSpeed);
			res->getSound("swoosh3.wav")->Play();
			return STATECHANGE::NONE;
		}
		return STATECHANGE::NONE;
	}

	if (!m_switchToMenu)
	{
		if (m_animationTimer >= m_animationLength)
		{
			m_switchToMenu = true;
			m_animationTimer = 0.;
			cam->SetTargetPos_rail(glm::vec3(30., 0., 3.), -90., 0., m_animationSpeed);
			return STATECHANGE::NONE;
		}
		return STATECHANGE::NONE;
	}

	if (m_switchToMenu)
	{
		std::cout << "DONE\n";
	}



	return STATECHANGE::NONE;
}

void IntroState::Render(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.f, 1.0f);

	res->Render(cam->getView(), cam->getProj());
}

void IntroState::ProcessKeyboard(GLFWwindow* window, Camera* cam, btDynamicsWorld* physicsWorld, Resource* res, float delta)
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
}