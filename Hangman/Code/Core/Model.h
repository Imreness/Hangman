#pragma once
#ifndef MODEL_CLASS
#define MODEL_CLASS

//Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Other dependencies
#include <vector>
#include "Shader.h"
#include "Texture.h"

//Model Loading
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

//3D basic model
class Model
{
private:
	//OpenGL
	unsigned int m_VAO, m_VBO, m_EBO;

	//Vertex Data
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indicies;

	//Dependencies
	Texture* m_tex;
	Shader*  m_shader;

	//ModelMatrix for OpenGL
	glm::mat4 m_model = glm::mat4(1.0f);

	//From file
	std::string LoadModel(const char* path);
	void SetupVAO();
public:

	Model() {};

	~Model();


	std::vector<Vertex> GetVertices() { return m_vertices; }


	std::string Setup(const char* Modelpath , Shader* shader);

	void AttachNewShader (Shader* shader) { m_shader = shader; }
	void AttachNewTexture(Texture* tex)   { m_tex = tex      ; }

	void Render(glm::mat4 &viewMatrix, glm::mat4 &projMatrix , bool useOverride = false, Texture* overrideTexture = nullptr);

	//Basic model manipulation
	void TranslateMatrix(glm::vec3 amount);
	void RotateMatrix(glm::vec3 amount, float angle);
	void ScaleMatrix(glm::vec3 amount);
};

#endif