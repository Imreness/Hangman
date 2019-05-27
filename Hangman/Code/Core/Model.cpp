#include "Model.h"

std::string Model::Setup(const char* Modelpath , Shader* shader)
{
	m_shader = shader;
	return LoadModel(Modelpath);
}

std::string Model::LoadModel(const char* path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::LOAD - FILE:\n" << path << "\nERROR:\n" << importer.GetErrorString() << "\n";
	}

	aiMesh* mesh = scene->mMeshes[scene->mRootNode->mChildren[0]->mMeshes[0]];

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.pos      = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y)      ;
		vertex.normal   = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z)   ;

		m_vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			m_indicies.push_back(face.mIndices[j]);
	}

	SetupVAO();

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];


	aiString str;
	material->GetTexture(aiTextureType_DIFFUSE, 0, &str);


	std::string texturePath(str.C_Str());
	texturePath = texturePath.substr(texturePath.find_first_of('\\') + 1);
	std::replace(texturePath.begin(), texturePath.end(), '\\', '/');

	

	return texturePath;

}

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

void Model::Render()
{
	m_shader->Use();
	m_tex->Use();

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indicies.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}