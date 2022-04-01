#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Object
{
public:
	// Members
	glm::vec3 position;
	float rotX;
	float rotY;
	float rotZ;

	glm::mat4 model;

	Model objModel;

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	Shader shader;
	Texture texture;

	int totalVertices;

	// Methods
	Object();
	Object(glm::vec3 position, glm::vec3 rotation);
	Object(glm::vec3 position, glm::vec3 rotation, const char* textureLocation, const char* vertexLocation, const char* fragmentLocation);
	~Object();

	void loadTexture(const char* textureLocation);
	void loadTexture(Texture newTexture);
	void loadShader(const char* vertex, const char* fragment);
	void loadModel();
	void loadModel(std::string path);
	void createModelMatrix();
	void update(float dt, std::map<int, bool>& keys);
	void draw();

	void destroyObject();

private:

};
