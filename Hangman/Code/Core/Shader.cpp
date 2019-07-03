#include "Shader.h"

void Shader::CheckError(unsigned int ID, bool isProgram)
{
	int success;
	char infolog[1024];

	if (isProgram)
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 1024, NULL, infolog);
			std::cout << "ERROR::SHADER::LINKING_SHADER_PROGRAM\n" << infolog;
		}
	}
	else
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 1024, NULL, infolog);
			std::cout << "ERROR::SHADER::COMPILING_SHADER\n" << infolog;
		}
	}
}


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//Load Shader from file
	std::ifstream vertexFile , fragmentFile;
	std::string   vertexString, fragmentString;

	vertexFile  .open(vertexPath);
	fragmentFile.open(fragmentPath);

	//Set it so the files could return an error
	//(but apparently this creates errors so idk)
	//vertexFile  .exceptions(std::ifstream::failbit | std::ifstream::badbit);
	//fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		std::stringstream vertexSstream, fragmentSstream;

		vertexSstream   << vertexFile.rdbuf();
		fragmentSstream << fragmentFile.rdbuf();

		vertexString    = vertexSstream.str();
		fragmentString  = fragmentSstream.str();
	}
	catch(std::ifstream::failure &e)
	{
		std::cout << "ERROR::SHADER::FAILED_TO_LOAD\n";
	}
	const char* vertexCode   = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource (vertex, 1, &vertexCode, NULL);
	glCompileShader(vertex);
	CheckError     (vertex, false);

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource (fragment, 1, &fragmentCode, NULL);
	glCompileShader(fragment);
	CheckError     (fragment, false);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram (m_ID);
	CheckError    (m_ID, true);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

//Setting uniforms
void Shader::setUniform(const char* name , glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name) , 1 , false , &value[0][0]);
}
void Shader::setUniform(const char* name, glm::mat3& value)
{
	glUniformMatrix3fv(glGetUniformLocation(m_ID, name), 1, true, &value[0][0]);
}
void Shader::setUniform(const char* name , int value)
{
	glUniform1i(glGetUniformLocation(m_ID, name), value);
}
void Shader::setUniform(const char* name, float value)
{
	glUniform1i(glGetUniformLocation(m_ID, name), value);
}
void Shader::setUniform(const char* name , glm::vec4& value)
{
	glUniform4fv(glGetUniformLocation(m_ID, name), 1, &value[0]);
}
void Shader::setUniform(const char* name , glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(m_ID, name), 1, &value[0]);
}
void Shader::setUniform(const char* name , glm::vec2& value)
{
	glUniform2fv(glGetUniformLocation(m_ID, name), 1, &value[0]);
}