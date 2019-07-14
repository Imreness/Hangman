#include "Resource.h"

Model* Resource::getModel(const char* path , const char* shaderName)
{
	//Format a name from the path
	std::string modelName(path);
	modelName = modelName.substr(modelName.find_first_of('/') + 1);
	std::cout << modelName << "\n";

	//Check if we already have that model loaded
	if (m_ModelPool.find(modelName) == m_ModelPool.end())
	{
		Model* model = new Model();
		//The model's setup returns the texture path
		model->AttachNewTexture(LoadTexture(model->Setup(path, getShader(shaderName)).c_str()));
		//Save it into the pool
		m_ModelPool[modelName] = model;
		return model;
	}
	else
		//just return the already loaded model
		return m_ModelPool[modelName];
}

//With the name, give it the extension(.jpg, .png, etc.)
Texture* Resource::getTexture(std::string name)
{
	if (m_TexturePool.find(name) == m_TexturePool.end())
	{
		std::cout << "ERROR::RESOURCE::GETTEXTURE - No texture named: " << name << " found.\n";
	}
	return m_TexturePool[name];
}

Texture* Resource::LoadTexture(const char* path)
{
	//Format a name from the path
	std::string textureName(path);
	textureName = textureName.substr(textureName.find_first_of('/') + 1);
	std::cout << textureName << "\n";

	//Check if we already have that texture loaded
	if (m_TexturePool.find(textureName) == m_TexturePool.end())
	{
		Texture* texture           = new Texture(path);
		m_TexturePool[textureName] = texture;
		return texture;
	}
	else
		//just return the already loaded texture
		return m_TexturePool[textureName];
}

Shader* Resource::loadShader(const char* vertexPath, const char* fragmentPath, std::string name)
{
	//Check if we already have that shader loaded
	if (m_ShaderPool.find(name) == m_ShaderPool.end())
	{
		Shader* shader     = new Shader(vertexPath , fragmentPath);
		m_ShaderPool[name] = shader;
		return shader;
	}
	else
		//just return the already loaded shader
		return m_ShaderPool[name];
}
//Get an ALREADY LOADED shader
Shader* Resource::getShader(std::string name)
{
	if (m_ShaderPool.find(name) == m_ShaderPool.end())
	{
		std::cout << "ERROR::RESOURCE::GETSHADER - No shader named: " << name << " found.\n";
	}
	return m_ShaderPool[name];
}

//Create an object
Object* Resource::SpawnObject(std::string name, const char* modelPath, const char* shaderName, btDynamicsWorld* physicsWorld, btTransform trans, bool textureOverride, Texture* tex)
{
	//Check if we already have that object spawned
	if (m_ObjectPool.find(name) == m_ObjectPool.end())
	{
		Object* obj;
		if (textureOverride)
			obj = new Object(name, getModel(modelPath, shaderName), physicsWorld, trans, true , tex);
		else
			obj = new Object(name, getModel(modelPath, shaderName), physicsWorld, trans);

		m_ObjectPool[name] = obj;
		return obj;
	}
	else
		//just return the already spawned object
		return m_ObjectPool[name];
}
//Get an ALREADY SPAWNED OBJECT
Object* Resource::getObject(std::string name)
{
	if (m_ObjectPool.find(name) == m_ObjectPool.end())
	{
		std::cout << "ERROR::RESOURCE::GETOBJECT - No object named: " << name << " found.\n";
	}
	return m_ObjectPool[name];
}

SoundEffect* Resource::loadSound(const char* path)
{
	std::string soundname(path);
	soundname = soundname.substr(soundname.find_first_of('/') + 1);
	std::cout << soundname << "\n";

	if (m_SoundPool.find(soundname) == m_SoundPool.end())
	{
		SoundEffect* sound = new SoundEffect(path);
		m_SoundPool[soundname] = sound;
		return sound;
	}
	else
		return m_SoundPool[soundname];
}

SoundEffect* Resource::getSound(std::string name)
{
	if (m_SoundPool.find(name) == m_SoundPool.end())
	{
		std::cout << "ERROR::RESOURCE::GETSOUND - No sound effect named: " << name << " found.\n";
	}
	return m_SoundPool[name];
}

Music* Resource::loadMusic(const char* path)
{
	std::string musicname(path);
	musicname = musicname.substr(musicname.find_first_of('/') + 1);
	std::cout << musicname << "\n";

	if (m_MusicPool.find(musicname) == m_MusicPool.end())
	{
		Music* music = new Music(path);
		m_MusicPool[musicname] = music;
		return music;
	}
	else
		return m_MusicPool[musicname];
}

Music* Resource::getMusic(std::string name)
{
	if (m_MusicPool.find(name) == m_MusicPool.end())
	{
		std::cout << "ERROR::RESOURCE::GETMUSIC - No music named: " << name << " found.\n";
	}
	return m_MusicPool[name];
}


//Render ALL objects in the objectPool
void Resource::Render(glm::mat4& viewMatrix, glm::mat4& projMatrix)
{
	for (auto obj : m_ObjectPool)
	{
		obj.second->Render(viewMatrix, projMatrix);
	}
}

void Resource::Clean()
{
	for (auto x : m_ObjectPool)
	{
		delete x.second;
	}
	m_ObjectPool.clear();

	for (auto x : m_ModelPool)
	{
		delete x.second;
	}
	m_ModelPool.clear();

	for (auto x : m_TexturePool)
	{
		delete x.second;
	}
	m_TexturePool.clear();

	for (auto x : m_ShaderPool)
	{
		delete x.second;
	}
	m_ShaderPool.clear();
}