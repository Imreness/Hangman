#include "Camera.h"
#include <iostream>

void Camera::Update(float delta)
{
	updateCameraVectors();
	if (m_camMode == CameraMode::ONRAILS &&  m_interpolationDone == false)
	{
		InterpolateToTarget(delta);
	}
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;

	//Calculate where should we "look"
	if (m_camMode == CameraMode::ONRAILS)
	{
		front.x = cos(glm::radians(m_yaw_rail)) * cos(glm::radians(m_pitch_rail));
		front.y = sin(glm::radians(m_pitch_rail));
		front.z = cos(glm::radians(m_pitch_rail)) * sin(glm::radians(m_yaw_rail));
	}
	else
	{
		front.x = cos(glm::radians(m_yaw_DEBUG)) * cos(glm::radians(m_pitch_DEBUG));
		front.y = sin(glm::radians(m_pitch_DEBUG));
		front.z = cos(glm::radians(m_pitch_DEBUG)) * sin(glm::radians(m_yaw_DEBUG));
	}

	front = glm::normalize(front);
	m_front = front;

	m_right = glm::normalize(glm::cross(m_front, m_up));
	
	m_view = glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::InterpolateToTarget(float delta)
{
	if (!m_interpolationDone)
	{
		m_interpolationTimer += delta;

		//All animation will have 5 seconds to finish. Thats more than enough
		if (m_interpolationTimer >= 5)
		{
			m_interpolationDone = true;
		}
	}

	//Interpolate the values with the MIX function
	m_position   = glm::mix(m_position  , m_targetPos  , m_interpolationTimer * m_interpolationSpeed);
	m_yaw_rail   = glm::mix(m_yaw_rail  , m_targetYaw  , m_interpolationTimer * m_interpolationSpeed);
	m_pitch_rail = glm::mix(m_pitch_rail, m_targetPitch, m_interpolationTimer * m_interpolationSpeed);
}

void Camera::SetMode(CameraMode newmode)
{
	//Set the interpolation to default values, so when switching from debug to rails one, the camera will take its original place
	m_interpolationDone  = false;
	m_interpolationTimer = 0;

	//Set the Debug's values to the on-rails one, so the camera wont just snap away when we switch modes
	m_yaw_DEBUG   = m_yaw_rail;
	m_pitch_DEBUG = m_pitch_rail;
	m_camMode     = newmode;
}

void Camera::SetTargetPos_rail(glm::vec3 pos, float yaw, float pitch, float interpolationSpeed)
{
	m_targetPitch = pitch; m_targetYaw = yaw; m_targetPos = pos;

	m_interpolationTimer = 0.;
	m_interpolationDone  = false;
	m_interpolationSpeed = interpolationSpeed;
}

Mouse3DPosition Camera::getMouse3DPositions(GLFWwindow* window)
{
	int windowWidth, windowHeight;

	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	//Get the mouse as Normalized Device coordinates (clamped between 0 and 1)
	glm::vec4 RayStart_NDC(
		(m_mouseX / windowWidth - 0.5f) * 2.f,
		((m_mouseY / windowHeight - 0.5f) * 2.f) * -1.f,
		-1.f,
		1.f
	);
	glm::vec4 RayEnd_NDC(
		(m_mouseX / windowWidth - 0.5f) * 2.f,
		((m_mouseY / windowHeight - 0.5f) * 2.f) * -1.f,
		0.f,
		1.f
	);

	
	//When we multiply the NDC values with M (Projection and View), we reverse the application of said matrixes,
	//So we get the proper World values of the cursor
	glm::mat4 M = glm::inverse(m_proj * m_view);

	glm::vec4 RayStart_world = M * RayStart_NDC; RayStart_world /= RayStart_world.w;
	glm::vec4 RayEnd_world   = M * RayEnd_NDC  ; RayEnd_world  /= RayEnd_world.w;

	glm::vec3 RayDir_world(RayEnd_world - RayStart_world);

	Mouse3DPosition positions;
	positions.Direction = glm::normalize(RayDir_world);
	positions.StartPos  = RayStart_world;
	return positions;
}

void Camera::Move_DEBUG(CameraMovement_DEBUG movement, float delta)
{
	if (m_camMode == CameraMode::DEBUG)
	{
		float speed = m_moveSpeed_DEBUG * delta;

		if (m_isSprinting_DEBUG)
		{
			speed *= m_moveSpeed_DEBUG_multiplier;
		}

		switch (movement)
		{
		case CameraMovement_DEBUG::FORWARDS:
			m_position += m_front * speed;
			break;
		case CameraMovement_DEBUG::BACKWARDS:
			m_position -= m_front * speed;
			break;
		case CameraMovement_DEBUG::LEFT:
			m_position -= m_right * speed;
			break;
		case CameraMovement_DEBUG::RIGHT:
			m_position += m_right * speed;
			break;
		default:
			break;
		}
	}
}

void Camera::Mouselook(float xpos, float ypos)
{
	if (m_camMode == CameraMode::DEBUG)
	{
		if (m_isLooking_DEBUG)
		{
			if (m_firstMouse_DEBUG)
			{
				m_lastx_DEBUG = xpos;
				m_lasty_DEBUG = ypos;

				m_firstMouse_DEBUG = false;
			}

			float xOffset = xpos - m_lastx_DEBUG;
			float yOffset = m_lasty_DEBUG - ypos;


			xOffset *= m_lookSens_DEBUG;
			yOffset *= m_lookSens_DEBUG;

			m_yaw_DEBUG += xOffset;
			m_pitch_DEBUG += yOffset;

			m_lastx_DEBUG = xpos;
			m_lasty_DEBUG = ypos;

			if (m_pitch_DEBUG >= 89.f)
				m_pitch_DEBUG = 89.f;
			else if (m_pitch_DEBUG < -89.f)
				m_pitch_DEBUG = -89.f;


			updateCameraVectors();
		}
	}
}

void Camera::UpdateMousePos(float xpos, float ypos)
{
	m_mouseX = xpos; m_mouseY = ypos;
}
