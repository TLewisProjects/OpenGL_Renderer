#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include "Shader.h"
#include "Texture.h"
#include "Object.h"

class App
{
public:
	// Members
	GLFWwindow* window;
	Object cube1;

	// Methods
	App();
	~App();

	int initializeWindow();
	void setupObjects();

private:

};