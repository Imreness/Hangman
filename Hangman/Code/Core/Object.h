#pragma once
#ifndef OBJECT_CLASS
#define OBJECT_CLASS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

#include <bullet/btBulletDynamicsCommon.h>

#include "Model.h"

//Higher level Object to hold Transform or to have other class' starting point
class Object
{
private:

	Model* m_model;

	std::string m_name;

	//3D space
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale   ;

	//Physics
	btRigidBody* m_body;
	btCollisionObject* m_colObject;
	btCollisionShape* m_colShape;
public:

	Object(std::string name ,Model* model, btDynamicsWorld* physicsWorld , btTransform trans);

	//TODO - Implement movement (move , rotate , scale)
	//once the physics engine is in place

	void Render(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);

	void Translate(glm::vec3 amount , bool resetLastpos = false);
	void Rotate(float x, float y, float z, bool resetLastrot = false);
	void Scale(glm::vec3 amount, bool resetLastscale = true);

	std::string getName() { return m_name; }

	void AttachNewShader(Shader* shader) { m_model->AttachNewShader(shader); }

};


#endif