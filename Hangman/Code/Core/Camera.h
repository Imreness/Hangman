#pragma once
#ifndef CAMERA_CLASS
#define CAMERA_CLASS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/64/glfw3.h>

enum class CameraMode
{
	DEBUG,
	ONRAILS
};

enum class CameraMovement_DEBUG
{
	FORWARDS,
	BACKWARDS,
	LEFT,
	RIGHT
};

class Camera
{
private:
	CameraMode m_camMode = CameraMode::DEBUG;

	glm::mat4 m_view = glm::mat4(1.0f);
	glm::mat4 m_proj = glm::mat4(1.0f);

	glm::vec3 m_position, m_front, m_up, m_right;

	float m_FOV = 45.0f;

	float m_yaw, m_pitch;

	//TODO - Implement ON-rails cam
	//DEBUG freecam
	//float m_moveSpeed, m_moveSpeed_multiplier;
	float m_lookSens_DEBUG = 1.f;
	float m_moveSpeed_DEBUG = 2.f, m_moveSpeed_DEBUG_multiplier = 3.f;
	float m_lastx_DEBUG, m_lasty_DEBUG;
	bool m_firstMouse_DEBUG = true, m_isLooking_DEBUG = false , m_isSprinting_DEBUG = false;


	void updateCameraVectors();



public:

	Camera(int screenWidth , int screenHeight ,  glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float mouseSens = 0.25f)
		: m_position(position), m_up(glm::vec3(0.0f, 1.0f, 0.0f)), m_lookSens_DEBUG(mouseSens)
	{
		m_proj = glm::perspective(m_FOV, (float)screenWidth / screenHeight, 0.01f, 100.0f);
		m_yaw  = -90.f;
		m_pitch=   0.f;
		updateCameraVectors();
	}

	glm::mat4& getView() { return m_view    ; }
	glm::mat4& getProj() { return m_proj    ; }
	glm::vec3& getPos()  { return m_position; }

	void Move_DEBUG(CameraMovement_DEBUG movement , float delta);

	void Mouselook(float xpos, float ypos);

	void Update() { updateCameraVectors(); }

	void setShouldLook_DEBUG(bool value) { m_isLooking_DEBUG = value; }
	void setFirstMouse_DEBUG(bool value) { m_firstMouse_DEBUG = value; }
	void setSprint_DEBUG(bool value) { m_isSprinting_DEBUG = value; }
	void setCursorLock_DEBUG(GLFWwindow* win,bool value)
	{
		if (value)
			glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void RecalculateProjection(int width, int height)
	{
		m_proj = glm::perspective(m_FOV, (float)width / height, 0.01f, 100.0f);
	}

};

#endif