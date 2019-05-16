#pragma once
#ifndef DELTA_TIME
#define DELTA_TIME
#include <GLFW/64/glfw3.h>

namespace DeltaTime
{
	static float deltaTime;
	static float lastFrame;
	static float currentFrame;

	void CalculateDelta()
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
}

#endif