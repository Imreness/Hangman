#include "Object.h"
void Object::Render(glm::mat4 &viewMatrix, glm::mat4 &projMatrix)
{
	m_model->Render(viewMatrix, projMatrix);
}

Object::Object(Model* model)
	: m_model(model)
{

}