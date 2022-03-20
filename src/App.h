#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include "Shader.h"
#include "Texture.h"

class App
{
public:
	// Members
	GLFWwindow* window;
	GLuint VAO1;
	GLuint VAO2;
	GLuint VAO3;

	GLuint VBO1;
	GLuint VBO2;
	GLuint VBO3;

	GLuint EBO1;
	
	Texture texture1;
	Shader shaderProgram1;
	Shader shaderProgram2;

	// Methods
	App();
	~App();

	int initializeWindow();
	void setupVertexBuffers();
	void setupShaderProgram();
	void loadTexture(const char* textureFile);

private:

};