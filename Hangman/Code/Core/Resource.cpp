#include "Resource.h"

Model* Resource::loadModel(const char* path, std::string name)
{
	Model* model = new Model();
	std::string texturePath = model->Setup(path);
	loadTexture("D:/Dev/Projects/Learning/LearnASSIMP/LearnASSIMP/Textures/box.jpg", "test");
	model->AttachTexture(m_TexturePool["test"]);
	m_ModelPool[name] = model;
	return model;
}
Model* Resource::getModel(std::string name)
{
	return m_ModelPool[name];
}

Texture* Resource::loadTexture(const char* path, std::string name)
{
	//TODO - Check if texture is already loaded
	std::cout << "Path:" << path << "\nName:" << name << "\n";
	Texture* texture = new Texture(path);
	if (this == nullptr)
	{
		std::cout << "DAFUQ???\n";
	}
	m_TexturePool["test"] = texture;
	return texture;
}
Texture* Resource::getTexture(std::string name)
{
	return m_TexturePool[name];
}

Shader* Resource::loadShader(const char* vertexPath, const char* fragmentPath, std::string name)
{
	if (m_ShaderPool.find(name) == m_ShaderPool.end())
	{
		Shader* shader = new Shader(vertexPath , fragmentPath);
		m_ShaderPool[name] = shader;
		return shader;
	}
	else
	{
		return m_ShaderPool[name];
	}
}
Shader* Resource::getShader(std::string name)
{
	return m_ShaderPool[name];
}