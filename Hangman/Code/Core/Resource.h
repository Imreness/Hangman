#pragma once
#ifndef RESOURCE_CLASS
#define RESOURCE_CLASS
#include <unordered_map>
#include <string>
#include "Model.h"


class Resource
{
private:
	std::unordered_map<std::string, Model*  > m_ModelPool  ;
	std::unordered_map<std::string, Texture*> m_TexturePool;
	std::unordered_map<std::string, Shader* > m_ShaderPool ;


	//TODO - Implement Cleaning
	void Clean()
	{

	}

public:

	Resource() {}

	Model* loadModel(const char* path, std::string name);
	Model* getModel (std::string name);

	Texture* loadTexture(const char* path, std::string name);
	Texture* getTexture (std::string name);

	Shader* loadShader(const char* vertexPath, const char* fragmentPath, std::string name);
	Shader* getShader(std::string name);

	~Resource() { Clean(); }

};

#endif 