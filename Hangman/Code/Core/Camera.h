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

struct Mouse3DPosition
{
	glm::vec3 Direction;
	glm::vec3 StartPos;
};

//An On-rails animation based or debug freecam for 3D
class Camera
{
private:
	//TODO
	//Start in Onrail mode once implemented
	CameraMode m_camMode = CameraMode::DEBUG;

	//OpenGL
	glm::mat4 m_view = glm::mat4(1.0f);
	glm::mat4 m_proj = glm::mat4(1.0f);

	//3D Space
	glm::vec3 m_position, m_front, m_up, m_right;

	//Field of view used for Onrails and debug cam
	float m_FOV = 45.0f;

	//TODO - Implement ON-rails cam
	float m_mouseX, m_mouseY;
	
	//DEBUG freecam parameters
	float m_yaw_DEBUG, m_pitch_DEBUG;

	//Input variables
	float m_lookSens_DEBUG = 1.f ,m_moveSpeed_DEBUG = 2.f, m_moveSpeed_DEBUG_multiplier = 3.f;

	//Mouse variables
	float m_lastx_DEBUG, m_lasty_DEBUG;
	bool m_firstMouse_DEBUG = true, m_isLooking_DEBUG = false , m_isSprinting_DEBUG = false;

	//Updates viewmatrix
	void updateCameraVectors();
public:

	Camera(int screenWidth , int screenHeight ,  glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float mouseSens = 0.25f)
		: m_position(position), m_up(glm::vec3(0.0f, 1.0f, 0.0f)), m_lookSens_DEBUG(mouseSens)
	{
		m_proj = glm::perspective(m_FOV, (float)screenWidth / screenHeight, 0.01f, 100.0f);
		m_yaw_DEBUG = -90.f;
		m_pitch_DEBUG =   0.f;
		updateCameraVectors();
	}

	Mouse3DPosition getMouse3DPositions(GLFWwindow* window);

	//Used by shaders for convinient access to matrixes
	glm::mat4& getView() { return m_view    ; }
	glm::mat4& getProj() { return m_proj    ; }
	glm::vec3& getPos()  { return m_position; }
	float getMouseX_DEBUG() { return m_lastx_DEBUG; }
	float getMouseY_DEBUG() { return m_lasty_DEBUG; }
	float getMouseX() { return m_mouseX; }
	float getMouseY() { return m_mouseY; }
	
	void Move_DEBUG(CameraMovement_DEBUG movement , float delta);

	//Used by both Onrails and debugcam
	void Mouselook(float xpos, float ypos);

	//Updates general Mouse position. This is used to get mouse coordinates easily.
	//It does NOT move the camera what so ever
	void UpdateMousePos(float xpos, float ypos);

	void Update() { updateCameraVectors(); }


	//Handful of parameter setting functions
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


	//While the window cant change, options will enable us to do so
	void RecalculateProjection(int width, int height)
	{
		m_proj = glm::perspective(m_FOV, (float)width / height, 0.01f, 100.0f);
	}
};

#endif