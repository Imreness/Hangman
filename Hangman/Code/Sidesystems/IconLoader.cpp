#include "IconLoader.h"

GLFWimage* IconLoader::LoadIcon(const char* path)
{
	int width = 0, height = 0, nrComponent = 0;

	unsigned char* data = stbi_load(path, &width, &height, &nrComponent, 0);

	GLFWimage* image = new GLFWimage();
	image->height = height;
	image->width = width;
	image->pixels = data;

	return image;
}