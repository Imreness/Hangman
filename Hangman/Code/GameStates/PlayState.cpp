#include "PlayState.h"

//Spawn in the blanks
void PlayState::SetupNewWord(Resource* res , btDynamicsWorld* physicsWorld)
{
	//Reset the session specific stuff
	m_lives = 10;
	m_guessedLetters = 0;

	//Delete all the blanks
	for (int i = 0; i < m_currWord.length(); i++)
	{
		std::string blankname("blank" + std::to_string(i));
		res->DespawnObject(blankname);
	}

	//Hide all of the hangman
	for (int i = 1; i < 11; i++)
	{
		std::string hangname("h_" + std::to_string(i));
		res->getObject(hangname)->setShouldRender(0);
	}

	
	btTransform objectTrans; objectTrans.setIdentity();
	objectTrans.setRotation(btQuaternion(0.5, 0., 0.));

	//Respawn all the letters
	for (int i = 0; i < 26; i++)
	{
		//Get Texture
		std::string filepath;
		filepath.append("Textures/letters/button_"); filepath.append(1, (char)(i + 97)); filepath.append(".png");
		Texture* letter = res->LoadTexture(filepath.c_str());

		//Figure out position
		//Positioning parameters
		float spacing = 0.4;
		float heightStart = 1.25;
		float heightDifference = 0.4;
		float sidewaysStart = -2.7;
		float sidewaysDifference = -2.2;
		float lastRowOffset = 0.35;

		float buttonScale = 0.125;

		if (i <= 5)
			objectTrans.setOrigin(btVector3((sidewaysStart)+(i * spacing), heightStart, 0));
		else if (i <= 11 && i > 5)
			objectTrans.setOrigin(btVector3(((sidewaysStart + (sidewaysDifference))) + (i * spacing), heightStart - heightDifference, 0));
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
		res->SpawnObject(objectName.c_str(), "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, letter)
			->Scale(glm::vec3(buttonScale, buttonScale, buttonScale));
	}


	//If the new word is longer than 20 characters, find a new one
	int wordcount = 0;
	do
	{
		m_currWord = res->getDictionary()->getRandomWord();
		wordcount = m_currWord.length();
	} while (wordcount > 20);

	//Reset tranformation
	objectTrans.setIdentity();

	Texture* blankTexure = res->LoadTexture("Textures/letters/button_unknown.png");


	float wordOffset = -0.15f;
	float pos = wordOffset * (wordcount - 1);
	//Spawn in the new blanks
	for (int i = 0; i < wordcount; i++)
	{
		objectTrans.setOrigin(btVector3(pos, -1.1, 0));
		std::string name("blank" + std::to_string(i));
		res->SpawnObject(name, "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, blankTexure)
			->Scale(glm::vec3(0.125, 0.125, 0.125));
		pos -= (wordOffset * 2);
	}
}

//Check the current word with a certain letter
void PlayState::CheckWord(Resource* res,Camera* cam,char letter)
{
	bool hasCharacter = false;

	//Check all of the characters
	for (int i = 0; i < m_currWord.length(); i++)
	{
		//If we guessed it right, change the blank's texture, and check for win condition
		if (m_currWord.at(i) == letter)
		{
			//If we guessed it right, flip the flag
			hasCharacter = true;

			std::string textureName("button_"); textureName.append(1,letter); textureName.append(".png");
			res->getObject(std::string("blank" + std::to_string(i)))->AttachNewOverrideTexture(res->getTexture(textureName));
			m_guessedLetters++;

			//Checking for win condition
			if (m_guessedLetters == m_currWord.length())
			{
				res->getObject("endgameLogo")->AttachNewOverrideTexture(res->getTexture("win.jpg"));
				m_state = MainGameStates::GAMEOVER;
				if (res->m_useChadWarden)
					res->getSound("win_chad.wav")->Play();
				else
					res->getSound("win.wav")->Play();
				cam->SetTargetPos_rail(glm::vec3(-10., 0., 3.), -90., 0.);


				//Move the blanks and complete the word
				for (int i = 0; i < m_currWord.length(); i++)
				{
					std::string blankname("blank" + std::to_string(i));
					Object* blankObj = res->getObject(blankname);
					blankObj->Translate(glm::vec3(-10, 0, 0));
					std::string letterName("button_"); letterName.append(1, m_currWord.at(i)); letterName.append(".png");
					blankObj->AttachNewOverrideTexture(res->getTexture(letterName));
				}
			}
		}
	}

	//Lower our lives, reveal hangman and check for lose condition
	if (!hasCharacter)
	{
		m_lives -= 1;

		std::string hangmanName("h_" + std::to_string(10-m_lives));
		res->getObject(hangmanName)->setShouldRender(1);

		//Check for lose condition
		if (m_lives == 0)
		{
			res->getObject("endgameLogo")->AttachNewOverrideTexture(res->getTexture("lose.jpg"));
			if (res->m_useChadWarden)
				res->getSound("lose_chad.wav")->Play();
			else
				res->getSound("lose.wav")->Play();
			m_state = MainGameStates::GAMEOVER;
			cam->SetTargetPos_rail(glm::vec3(-10., 0., 3.), -90., 0.);

			//Move the blanks and complete the word
			for (int i = 0; i < m_currWord.length(); i++)
			{
				std::string blankname("blank" + std::to_string(i));
				Object* blankObj = res->getObject(blankname);
				blankObj->Translate(glm::vec3(-10, 0, 0));
				std::string letterName("button_"); letterName.append(1, m_currWord.at(i)); letterName.append(".png");
				blankObj->AttachNewOverrideTexture(res->getTexture(letterName));
			}
		}
	}

	//Delete the selected letter button
	res->DespawnObject(std::string(1,letter));
}


void PlayState::Setup(GLFWwindow* window, Resource* res, Camera* cam, btDynamicsWorld* physicsWorld)
{
	//Load general resources
	res->loadShader("Shaders/object.vert", "Shaders/object.frag", "basicShader");
	res->loadSound("Audio/click.wav");
	res->loadSound("Audio/click.wav");

	if (!res->m_useChadWarden)
	{
		res->loadSound("Audio/win.wav");
		res->loadSound("Audio/lose.wav");
	}
	else
	{
		res->loadSound("Audio/win_chad.wav");
		res->loadSound("Audio/lose_chad.wav");
	}

	if (res->m_dictionaryUseCustomWords)
		res->LoadDictionary("customwordlist.txt");
	else
		res->LoadDictionary("default.wordlist");

	btTransform objectTrans; objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(0, 0., 0.));
	objectTrans.setRotation(btQuaternion(0.5 , 0. , 0.));

	//Setup Game Area
	{
		//Spawn in the letters
		for (int i = 0; i < 26; i++)
		{
			//Get Texture
			std::string filepath;
			filepath.append("Textures/letters/button_"); filepath.append(1, (char)(i + 97)); filepath.append(".png");
			Texture* letter = res->LoadTexture(filepath.c_str());

			//Figure out position
			//Positioning parameters
			float spacing = 0.4;
			float heightStart = 1.25;
			float heightDifference = 0.4;
			float sidewaysStart = -2.7;
			float sidewaysDifference = -2.2;
			float lastRowOffset = 0.35;

			float buttonScale = 0.125;

			if (i <= 5)
				objectTrans.setOrigin(btVector3((sidewaysStart)+(i * spacing), heightStart, 0));
			else if (i <= 11 && i > 5)
				objectTrans.setOrigin(btVector3(((sidewaysStart + (sidewaysDifference))) + (i * spacing), heightStart - heightDifference, 0));
			else if (i <= 17 && i > 11)
				objectTrans.setOrigin(btVector3(((sidewaysStart + (sidewaysDifference * 2))) + (i * spacing), heightStart - (heightDifference * 2), 0));
			else if (i <= 23 && i > 17)
				objectTrans.setOrigin(btVector3(((sidewaysStart + (sidewaysDifference * 3))) + (i * spacing), heightStart - (heightDifference * 3), 0));
			else if (i > 23)
				objectTrans.setOrigin(btVector3((((sidewaysStart + (sidewaysDifference * 4))) + (i * spacing)) + lastRowOffset, heightStart - (heightDifference * 4), 0));
			else if (i == 0)
				objectTrans.setOrigin(btVector3((sidewaysStart), 1.25, 0));

			//Put it together and spawning
			std::string objectName;
			objectName.append(1, (char)(i + 97));
			res->SpawnObject(objectName.c_str(), "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, letter)
				->Scale(glm::vec3(buttonScale, buttonScale, buttonScale));
		}

		btTransform objectTrans; objectTrans.setIdentity(); objectTrans.setOrigin(btVector3(0.85, -0.5, 0.)); objectTrans.setRotation(btQuaternion(-1.95, -1.58, 0));
		Texture* hangmantexture = res->LoadTexture("Textures/black.jpg");

		float hangmanScale = 0.25;

		//Load in the hangman (h_ means hangman)
		{
		res->SpawnObject("h_1", "Models/hangman/h_base.assbin", "basicShader", nullptr, objectTrans, true, hangmantexture)
			->Scale(glm::vec3(hangmanScale, hangmanScale, hangmanScale));
		res->getObject("h_1")->setShouldRender(0);

		res->SpawnObject("h_2", "Models/hangman/h_pole.assbin", "basicShader", nullptr, objectTrans, true, hangmantexture)
			->Scale(glm::vec3(hangmanScale, hangmanScale, hangmanScale));
		res->getObject("h_2")->setShouldRender(0);

		res->SpawnObject("h_3", "Models/hangman/h_overhead.assbin", "basicShader", nullptr, objectTrans, true, hangmantexture)
			->Scale(glm::vec3(hangmanScale, hangmanScale, hangmanScale));
		res->getObject("h_3")->setShouldRender(0);

		res->SpawnObject("h_4", "Models/hangman/h_rope.assbin", "basicShader", nullptr, objectTrans, true, hangmantexture)
			->Scale(glm::vec3(hangmanScale, hangmanScale, hangmanScale));
		res->getObject("h_4")->setShouldRender(0);

		res->SpawnObject("h_5", "Models/hangman/h_head.assbin", "basicShader", nullptr, objectTrans, true, hangmantexture)
			->Scale(glm::vec3(hangmanScale, hangmanScale, hangmanScale));
		res->getObject("h_5")->setShouldRender(0);

		res->SpawnObject("h_6", "Models/hangman/h_body.assbin", "basicShader", nullptr, objectTrans, true, hangmantexture)
			->Scale(glm::vec3(hangmanScale, hangmanScale, hangmanScale));
		res->getObject("h_6")->setShouldRender(0);

		res->SpawnObject("h_7", "Models/hangman/h_rarm.assbin", "basicShader", nullptr, objectTrans, true, hangmantexture)
			->Scale(glm::vec3(hangmanScale, hangmanScale, hangmanScale));
		res->getObject("h_7")->setShouldRender(0);

		res->SpawnObject("h_8", "Models/hangman/h_larm.assbin", "basicShader", nullptr, objectTrans, true, hangmantexture)
			->Scale(glm::vec3(hangmanScale, hangmanScale, hangmanScale));
		res->getObject("h_8")->setShouldRender(0);

		res->SpawnObject("h_9", "Models/hangman/h_rleg.assbin", "basicShader", nullptr, objectTrans, true, hangmantexture)
			->Scale(glm::vec3(hangmanScale, hangmanScale, hangmanScale));
		res->getObject("h_9")->setShouldRender(0);

		res->SpawnObject("h_10", "Models/hangman/h_lleg.assbin", "basicShader", nullptr, objectTrans, true, hangmantexture)
			->Scale(glm::vec3(hangmanScale, hangmanScale, hangmanScale));
		res->getObject("h_10")->setShouldRender(0);
		}

	}

	//Spawn in the blanks
	SetupNewWord(res, physicsWorld);

	//Setup Menu
	{
		objectTrans.setIdentity(); objectTrans.setRotation(btQuaternion(-1.58, 0, 0));

		objectTrans.setOrigin(btVector3(4., 1., 5.));
		Texture* pauseTex = res->LoadTexture("Textures/pause.jpg");
		res->SpawnObject("pauseLogo", "Models/banner.assbin", "basicShader", physicsWorld, objectTrans, true, pauseTex)
			->Scale(glm::vec3(0.5, 0.5, 0.5));

		
		objectTrans.setOrigin(btVector3(4., -0.35, 3.5));
		Texture* backPauseTexture = res->LoadTexture("Textures/button_back.png");
		res->SpawnObject("b_back", "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, backPauseTexture)
			->Scale(glm::vec3(0.45, 0.45, 0.45));

		objectTrans.setOrigin(btVector3(4., -0.35, 5.));
		Texture* newwordTexture = res->LoadTexture("Textures/button_newword.png");
		res->SpawnObject("b_newword", "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, newwordTexture)
			->Scale(glm::vec3(0.45, 0.45, 0.45));

		objectTrans.setOrigin(btVector3(4., -0.35, 6.5));
		Texture* mainmenuTexture = res->LoadTexture("Textures/button_mainmenu.png");
		res->SpawnObject("b_mainmenu", "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, mainmenuTexture)
			->Scale(glm::vec3(0.45, 0.45, 0.45));


	}

	//Setup endgame screen
	{
		objectTrans.setIdentity(); objectTrans.setRotation(btQuaternion(0, 0, 0));

		objectTrans.setOrigin(btVector3(-10., 1., 0.));
		Texture* endgameTexture = res->LoadTexture("Textures/lose.jpg"); res->LoadTexture("Textures/win.jpg");
		res->SpawnObject("endgameLogo", "Models/banner.assbin", "basicShader", physicsWorld, objectTrans, true, endgameTexture)
			->Scale(glm::vec3(0.5, 0.5, 0.5));

		objectTrans.setOrigin(btVector3(-10., 0., 0.));
		Texture* yourwordTexture = res->LoadTexture("Textures/yourwordwas.jpg");
		res->SpawnObject("yourwordLogo", "Models/banner.assbin", "basicShader", nullptr, objectTrans, true, yourwordTexture)
			->Scale(glm::vec3(0.25, 0.25, 0.25));

		objectTrans.setOrigin(btVector3(-11.5, -0.0, 0));
		Texture* playagainTexture = res->LoadTexture("Textures/button_playagain.png");
		res->SpawnObject("b_playagain", "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, playagainTexture)
			->Scale(glm::vec3(0.45, 0.45, 0.45));

		objectTrans.setOrigin(btVector3(-8.5, -0.0, 0));
		Texture* mainmenuTexture = res->LoadTexture("Textures/button_mainmenu.png");
		res->SpawnObject("b_mainmenu_endscreen", "Models/button.assbin", "basicShader", physicsWorld, objectTrans, true, mainmenuTexture)
			->Scale(glm::vec3(0.45, 0.45, 0.45));
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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		if (m_state == MainGameStates::MENU && !m_escapePressed)
		{
			m_state = MainGameStates::INGAME;
			m_escapePressed = true;
			cam->SetTargetPos_rail(glm::vec3(0., 0., 3.), -90., 0.);
		}
		else if (m_state == MainGameStates::INGAME && !m_escapePressed)
		{
			m_state = MainGameStates::MENU;
			m_escapePressed = true;
			cam->SetTargetPos_rail(glm::vec3(1., 0., 5.), 0., 0.);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
		m_escapePressed = false;

	if (glfwGetMouseButton(window, 0) == GLFW_RELEASE)
		m_mouseClicked = false;

	if (glfwGetKey(window, GLFW_KEY_F6) == GLFW_PRESS)
	{
		switch (m_state)
		{
		case MainGameStates::INGAME:
			std::cout << "ingame\n";
			break;
		case MainGameStates::MENU:
			std::cout << "menu\n";
			break;
		case MainGameStates::GAMEOVER:
			std::cout << "gameover\n";
			break;
		default:
			break;
		}
	}

	//Mouse Clickage
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
			if (m_state == MainGameStates::INGAME)
			{
				//Check if the button is one of the letters
				for (int i = 0; i < 26; i++)
				{
					std::string name(1, (char)i + 97);
					if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == name)
					{
						//std::cout << "hit " << (char)(i + 97) << "\n";
						CheckWord(res, cam, (char)(i + 97));
						res->getSound("click.wav")->Play();
						break;
					}
				}
			}
			else if (m_state == MainGameStates::MENU)
			{
				if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_back")
				{
					m_state = MainGameStates::INGAME;
					res->getSound("click.wav")->Play();
					cam->SetTargetPos_rail(glm::vec3(0., 0., 3.), -90., 0.);
				}
				if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_newword")
				{
					m_state = MainGameStates::INGAME;
					res->getSound("click.wav")->Play();
					cam->SetTargetPos_rail(glm::vec3(0., 0., 3.), -90., 0.);
					SetupNewWord(res, physicsWorld);
				}
				else if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_mainmenu")
				{
					res->getSound("click.wav")->Play();
					m_changeToMenu = true;
				}
			}
			else if (m_state == MainGameStates::GAMEOVER)
			{
				if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_playagain")
				{
					m_state = MainGameStates::INGAME;
					res->getSound("click.wav")->Play();
					cam->SetTargetPos_rail(glm::vec3(0., 0., 3.), -90., 0.);
					SetupNewWord(res, physicsWorld);
				}
				else if (((Object*)rayCallback.m_collisionObject->getUserPointer())->getName() == "b_mainmenu_endscreen")
				{
					res->getSound("click.wav")->Play();
					m_changeToMenu = true;
				}
			}
		}
	}

	//DEBUG Camera Input
	/*{
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

	}*/
}