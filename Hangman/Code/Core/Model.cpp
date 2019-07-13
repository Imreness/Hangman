#include "Model.h"

std::string Model::Setup(const char* Modelpath , Shader* shader)
{
	m_shader = shader;
	//Returns loaded model's texture path
	return LoadModel(Modelpath);
}

//Return loaded model's texture path
std::string Model::LoadModel(const char* path)
{
	//Import model
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	//Check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::LOAD - FILE:\n" << path << "\nERROR:\n" << importer.GetErrorString() << "\n";
	}

	//Get the first mesh
	aiMesh* mesh = scene->mMeshes[scene->mRootNode->mChildren[0]->mMeshes[0]];

	//Process vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.pos      = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y)      ;
		vertex.normal   = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z)   ;

		m_vertices.push_back(vertex);
	}
	
	//Process indicies
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			m_indicies.push_back(face.mIndices[j]);
	}


	SetupVAO();

	//Get texture path
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	aiString str;
	material->GetTexture(aiTextureType_DIFFUSE, 0, &str);

	//Format texture path so we can use it in our texture class
	std::string texturePath(str.C_Str());
	texturePath = texturePath.substr(texturePath.find_first_of('\\') + 1);
	std::replace(texturePath.begin(), texturePath.end(), '\\', '/');

	

	return texturePath;

}

//General OpenGL VAO setting-up
void Model::SetupVAO()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicies.size() * sizeof(unsigned int), &m_indicies[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::texCoord));

	glBindVertexArray(0);
}

void Model::Render(glm::mat4& viewMatrix, glm::mat4& projMatrix, bool useOverride, Texture* overrideTexture)
{
	m_shader->Use();
	if (useOverride)
		overrideTexture->Use();
	else
		m_tex   ->Use();

	m_shader->setUniform("modelMat", m_model   );
	m_shader->setUniform("viewMat" , viewMatrix);
	m_shader->setUniform("projMat" , projMatrix);

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indicies.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Model::TranslateMatrix(glm::vec3 amount)
{
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, amount);
}

void Model::RotateMatrix(glm::vec3 amount, float angle)
{
	//We dont reset the Matrix, since Translate will be called first, and it already does that
	m_model = glm::rotate(m_model, angle, amount);
}

void Model::ScaleMatrix(glm::vec3 amount)
{
	//We dont reset the Matrix, since Translate will be called first, and it already does that
	m_model = glm::scale(m_model, amount);
}

Model::~Model()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers     (1, &m_VBO);
	glDeleteBuffers     (1, &m_EBO);

	m_vertices.clear();
	m_indicies.clear();
}