#include "Object.h"
void Object::Render()
{
	m_model->Render();
}

Object::Object(Model* model)
	: m_model(model)
{

}