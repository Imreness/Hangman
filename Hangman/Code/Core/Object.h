#pragma once
#ifndef OBJECT_CLASS
#define OBJECT_CLASS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include "Model.h"

class Object
{
private:

	Model* m_model;

	glm::mat4 m_view = glm::mat4(1.0f);

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale   ;

public:

	Object(Model* model);

	//TODO - Implement movement (move , rotate , scale)
	//once the physics engine is in place

	void Render(Shader* shader);

};


#endif