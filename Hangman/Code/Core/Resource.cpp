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
	//TODO - Check if texture is already loaded
	Texture* texture = new Texture(path);

	std::string textureName(path);
	textureName = textureName.substr(textureName.find_first_of('\\') + 1);
	std::cout << textureName << "\n";

	m_TexturePool[textureName] = texture;
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