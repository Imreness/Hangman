#pragma once
#ifndef DELTA_TIME_CLASS
#define DELTA_TIME_CLASS
#include <GLFW/64/glfw3.h>

namespace DeltaTime
{
	static double deltaTime;
	static double lastFrame;
	static double currentFrame;

	void CalculateDelta()
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
}

#endif