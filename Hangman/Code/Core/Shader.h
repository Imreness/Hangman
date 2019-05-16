#pragma once
#ifndef _SHADER_CLASS_
#define _SHADER_CLASS_

//OpenGL
#include <glad/glad.h>

//Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//IO
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class Shader
{
private:
	unsigned int m_ID;

	void CheckError(unsigned int ID, bool isProgram);

public:
	Shader(const char* vertexPath, const char* fragmentPath);

	void Use() { glUseProgram(m_ID); }

	//Setting values (Matrixes , vectors etc.)
	void setUniform(const char* name , int        value);
	void setUniform(const char* name , float      value);
	void setUniform(const char* name , glm::mat4& value);
	void setUniform(const char* name , glm::mat3& value);
	void setUniform(const char* name , glm::vec4& value);
	void setUniform(const char* name , glm::vec3& value);
	void setUniform(const char* name , glm::vec2& value);
};

#endif