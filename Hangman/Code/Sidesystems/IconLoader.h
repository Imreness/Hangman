#pragma once
#ifndef ICONLOADER_CLASS
#define ICONLOADER_CLASS
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

static class IconLoader
{
private:

public:

	static GLFWimage* LoadIcon(const char* path);


};

#endif