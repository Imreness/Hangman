#pragma once
#ifndef RESOURCE_CLASS
#define RESOURCE_CLASS
#include <unordered_map>
#include <string>
#include "Model.h"
#include "Object.h"

class Resource
{
private:
	//TODO - Put this into the Graphics Class
	std::unordered_map<std::string, Object* > m_ObjectPool ;

	std::unordered_map<std::string, Model*  > m_ModelPool  ;
	std::unordered_map<std::string, Texture*> m_TexturePool;
	std::unordered_map<std::string, Shader* > m_ShaderPool ;


	Model* getModel(const char* path , const char* shaderName);
	Texture* getTexture(const char* path);

	void Clean();

public:
	Resource() {}

	void Render(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);

	Object* SpawnObject(std::string name, const char* modelPath , const char* shaderName);
	Object* getObject(std::string name);

	Shader* loadShader(const char* vertexPath, const char* fragmentPath, std::string name);
	Shader* getShader(std::string name);

	~Resource() { Clean(); }



};

#endif 