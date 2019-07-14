#pragma once
#ifndef RESOURCE_CLASS
#define RESOURCE_CLASS
#include <unordered_map>
#include <string>
#include "Model.h"
#include "Object.h"
#include "SoundEffect.h"
#include "Music.h"

#include <bullet/btBulletDynamicsCommon.h>

//A class to hold other media(models, textures, shaders)
class Resource
{
private:
	//Higher-level pools
	std::unordered_map<std::string, Object* > m_ObjectPool ;

	//Lower-level pool
	std::unordered_map<std::string, Model*  > m_ModelPool  ;
	std::unordered_map<std::string, Texture*> m_TexturePool;
	std::unordered_map<std::string, Shader* > m_ShaderPool ;
	std::unordered_map<std::string, SoundEffect*> m_SoundPool;
	std::unordered_map<std::string, Music*> m_MusicPool;


	Model*   getModel  (const char* path , const char* shaderName);

	//Clean all pools
	void Clean();
public:
	Resource() {}

	Texture* getTexture(std::string name);
	Texture* LoadTexture(const char* path);

	void Render(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);

	Object* SpawnObject(std::string name, const char* modelPath, const char* shaderName, btDynamicsWorld* physicsWorld, btTransform trans, bool textureOverride = false , Texture* tex = nullptr);
	Object* getObject  (std::string name);

	Shader* loadShader(const char* vertexPath, const char* fragmentPath, std::string name);
	Shader* getShader (std::string name);

	SoundEffect* loadSound(const char* path);
	SoundEffect* getSound(std::string name);

	Music* loadMusic(const char* path);
	Music* getMusic(std::string name);

	~Resource() { Clean(); }
};

#endif 