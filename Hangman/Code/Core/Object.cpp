#include "Object.h"
void Object::Render(Shader* shader)
{
	m_model->Render(shader);
}

Object::Object(Model* model)
	: m_model(model)
{

}