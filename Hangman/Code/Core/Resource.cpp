#include "Resource.h"

Model* Resource::getModel(const char* path)
{
	std::string modelName(path);
	modelName = modelName.substr(modelName.find_first_of('/') + 1);
	std::cout << modelName << "\n";

	if (m_ModelPool.find(modelName) == m_ModelPool.end())
	{
		Model* model = new Model();
		//The model's setup returns the texture path
		model->AttachTexture(getTexture(model->Setup(path).c_str()));
		m_ModelPool[modelName] = model;
		return model;
	}
	else
		return m_ModelPool[modelName];
}

Texture* Resource::getTexture(const char* path)
{
	std::string textureName(path);
	textureName = textureName.substr(textureName.find_first_of('/') + 1);
	std::cout << textureName << "\n";

	if (m_TexturePool.find(textureName) == m_TexturePool.end())
	{
		Texture* texture = new Texture(path);
		m_TexturePool[textureName] = texture;
		return texture;
	}
	else
		return m_TexturePool[textureName];
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

Object* Resource::SpawnObject(std::string name, const char* modelPath)
{
	if (m_ObjectPool.find(name) == m_ObjectPool.end())
	{
		Object* obj = new Object(getModel(modelPath));
		m_ObjectPool[name] = obj;
		return obj;
	}
	else
	{
		return m_ObjectPool[name];
	}
}
Object* Resource::getObject(std::string name)
{
	return m_ObjectPool[name];
}