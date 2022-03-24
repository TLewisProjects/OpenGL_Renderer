#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

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
	std::vector<Object> cubes;
	int numCubes;

	Camera camera;
	glm::vec2 lastMousePos;
	bool firstMouse;

	int width;
	int height;

	// Methods
	App();
	App(int width, int height);
	~App();

	int initializeWindow(int width, int height);
	void setupObjects();
	void setupCamera();

private:

};