#pragma once
#ifndef TEXTURE_CLASS
#define TEXTURE_CLASS
#include <glad/glad.h>
#include <iostream>

class Texture
{
private:
	unsigned int m_ID;
public:
	Texture(const char* path);

	void Use()
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
};

#endif