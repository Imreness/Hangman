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

	bool m_shouldRender = true;

	//3D space
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale   ;

	//Texture overriding
	Texture* m_overrideTexture;
	bool m_boolOverrideTexture;

	//Physics
	btRigidBody*       m_body;
	btCollisionShape*  m_colShape;
	btDynamicsWorld*   m_parentWorld;
public:

	~Object();
	Object(std::string name, Model* model, btDynamicsWorld* physicsWorld, btTransform trans, bool textureOverdrive = false, Texture* tex = nullptr);

	void Render(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);

	void setShouldRender(bool value) { m_shouldRender = value; }

	//Object Manipulation
	void Translate(glm::vec3 amount , bool resetLastpos = false);
	void Rotate   (float x, float y, float z, bool resetLastrot = false);
	void Scale    (glm::vec3 amount, bool resetLastscale = true);

	std::string getName() { return m_name; }

	void AttachNewShader(Shader* shader)    { m_model->AttachNewShader(shader);   }
	void AttachNewTexture(Texture* texture) { m_model->AttachNewTexture(texture); }
	void AttachNewOverrideTexture(Texture* texture) { m_boolOverrideTexture = true; m_overrideTexture = texture; }

};


#endif