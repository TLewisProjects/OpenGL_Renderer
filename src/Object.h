#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"

class Object
{
public:
	// Members
	glm::vec3 position;
	float rotX;
	float rotY;
	float rotZ;

	glm::mat4 model;

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	Shader shader;
	Texture texture;

	// Methods
	Object();
	Object(glm::vec3 position, glm::vec3 rotation);
	Object::Object(glm::vec3 position, glm::vec3 rotation, const char* textureLocation, const char* vertexLocation, const char* fragmentLocation)
	~Object();

	void loadTexture(const char* textureLocation);
	void loadTexture(Texture newTexture);
	void loadShader(const char* vertex, const char* fragment);
	void loadModel();
	void createModelMatrix();

private:

};
