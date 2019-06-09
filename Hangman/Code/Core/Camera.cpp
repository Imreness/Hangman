#include "Camera.h"
#include <iostream>

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));

	front = glm::normalize(front);
	m_front = front;

	m_right = glm::normalize(glm::cross(m_front, m_up));
	
	m_view = glm::lookAt(m_position, m_position + m_front, m_up);
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
	//TODO
	//Implement an "onrails" looking, where if you move the mouse
	//the camera just slightly tries to look in that direction, real subtle stuff
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

			m_yaw += xOffset;
			m_pitch += yOffset;

			m_lastx_DEBUG = xpos;
			m_lasty_DEBUG = ypos;

			if (m_pitch >= 89.f)
				m_pitch = 89.f;
			else if (m_pitch < -89.f)
				m_pitch = -89.f;


			updateCameraVectors();
		}
	}
}