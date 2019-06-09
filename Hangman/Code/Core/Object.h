#pragma once
#ifndef OBJECT_CLASS
#define OBJECT_CLASS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"

//Higher level Object to hold Transform or to have other class' starting point
class Object
{
private:

	Model* m_model;

	//3D space
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale   ;

public:

	Object(Model* model);

	//TODO - Implement movement (move , rotate , scale)
	//once the physics engine is in place

	void Render(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);

	void AttachNewShader(Shader* shader) { m_model->AttachNewShader(shader); }

};


#endif