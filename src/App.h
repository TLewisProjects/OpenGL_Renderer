#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include "Shader.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"

class App
{
public:
	// Members
	GLFWwindow* window;
	Object cube1;
	Camera camera;
	glm::vec2 lastMousePos;
	bool firstMouse;

	// Methods
	App();
	~App();

	int initializeWindow();
	void setupObjects();
	void setupCamera();

private:

};