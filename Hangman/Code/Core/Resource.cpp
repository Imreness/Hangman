#include "Resource.h"

Model* Resource::loadModel(const char* path, std::string name)
{
	Model* model = new Model();
	model->AttachTexture(loadTexture(model->Setup(path).c_str()));
	return model;
}
Model* Resource::getModel(std::string name)
{
	return m_ModelPool[name];
}

Texture* Resource::loadTexture(const char* path)
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