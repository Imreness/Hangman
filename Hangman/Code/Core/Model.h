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

	std::string LoadModel(const char* path);
	void SetupVAO();
public:

	//TODO - Tidy up, make it so we can the texture in one single Setup call

	Model() {};

	std::string Setup(const char* Modelpath);

	void AttachTexture(Texture* tex) { m_tex = tex; }

	void Render(Shader* shader);
};

#endif