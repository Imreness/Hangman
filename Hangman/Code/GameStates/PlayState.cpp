#include "PlayState.h"

void PlayState::Setup(GLFWwindow* window, Resource* res, Camera* cam, btDynamicsWorld* physicsWorld)
{
	res->loadShader("Shaders/object.vert", "Shaders/object.frag", "basicShader");

	btTransform objectTrans; objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(0, 0., 0.));
	res->loadSound("Audio/click.wav");

	for (int i = 0; i < 26; i++)
	{
		//Get Texture
		std::string filepath;
		filepath.append("Textures/letters/button_"); filepath.append(1,(char)(i + 97)); filepath.append(".png");
		Texture* letter = res->LoadTexture(filepath.c_str());

		//Figure out position

		//Positioning parameters
		float spacing = 0.3;
		float heightStart = 1.25;
		float heightDifference = 0.4;
		float sidewaysStart = -2.5;
		float sidewaysDifference = -1.6;
		float lastRowOffset = 0.35;

		float buttonScale = 0.125;

		if (i <= 5)
			objectTrans.setOrigin(btVector3((sidewaysStart) + (i * spacing) , heightStart, 0));
		else if (i <= 11 && i > 5)
			objectTrans.setOrigin(btVector3(((sidewaysStart + (sidewaysDifference)))+ (i * spacing), heightStart - heightDifference , 0));
		else if (i <= 17 && i > 11)
			objectTrans.setOrigin(btVector3(((sidewaysStart + (sidewaysDifference * 2))) + (i * spacing), heightStart - (heightDifference * 2), 0));
		else if (i <= 23 && i > 17)
			objectTrans.setOrigin(btVector3(((sidewaysStart + (sidewaysDifference * 3))) + (i * spacing), heightStart - (heightDifference * 3), 0));
		else if (i > 23)
			objectTrans.setOrigin(btVector3((((sidewaysStart + (sidewaysDifference * 4))) + (i * spacing)) + lastRowOffset, heightStart - (heightDifference * 4), 0));
		else if (i == 0)
			objectTrans.setOrigin(btVector3((sidewaysStart), 1.25, 0));

		//Put it together
		std::string objectName;
		objectName.append(1, (char)(i + 97));
		res->SpawnObject(objectName.c_str(), "Models/button.blend", "basicShader", physicsWorld, objectTrans, true, letter)
			->Scale(glm::vec3(buttonScale, buttonScale, buttonScale));
	}

	cam->SetTransform(glm::vec3(0., 0., 3.), -90., 0.);
}

STATECHANGE PlayState::Update(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld, float delta)
{
	cam->Update(delta);

	if (m_changeToMenu)
		return STATECHANGE::MAINMENU;
	else
		return STATECHANGE::NONE;
}

void PlayState::Render(Resource* res, Camera* cam, btDynamicsWorld* physicsWorld)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.f, 1.0f);

	res->Render(cam->getView(), cam->getProj());
}

void PlayState::ProcessKeyboard(GLFWwindow* window, Camera* cam, btDynamicsWorld* physicsWorld, Resource* res, float delta)
{
	if (glfwGetKey(window, GLFW_KEY_F9) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_changeToMenu = true;
	}

	if (glfwGetMouseButton(window, 0) == GLFW_RELEASE)
		m_mouseClicked = false;

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