#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(const char* path)
{
	glGenTextures(1, &m_ID);

	int width = 0, height = 0, nrComponent = 0;

	unsigned char* data = stbi_load(path, &width, &height, &nrComponent, 0);
	if (data)
	{
		GLenum format;
		if (nrComponent == 1)
			format = GL_RED;
		else if (nrComponent == 3)
			format = GL_RGB;
		else if (nrComponent == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);

	}
	else
	{
		std::cout << "ERROR::STBI::LOAD - FAILED TO LOAD FILE AT:\n" << path << "\n";
	}
}