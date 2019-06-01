#pragma once
#ifndef MODEL_CLASS
#define MODEL_CLASS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Shader.h"
#include "Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};


class Model
{
private:
	//OpenGL
	unsigned int m_VAO, m_VBO, m_EBO;

	//Vertex Data
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indicies;

	Texture* m_tex;
	Shader* m_shader;

	std::string LoadModel(const char* path);
	void SetupVAO();
public:

	Model() {};

	~Model();

	std::string Setup(const char* Modelpath , Shader* shader);

	void AttachNewShader(Shader* shader) { m_shader = shader; }

	void AttachTexture(Texture* tex) { m_tex = tex; }

	void Render();
};

#endif