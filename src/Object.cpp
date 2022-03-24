#include "Object.h"

Object::Object() 
{

}

Object::Object(glm::vec3 position, glm::vec3 rotation)
{
	this->position = position;
	this->rotX = rotation.x;
	this->rotY = rotation.y;
	this->rotZ = rotation.z;
	this->totalVertices = 0;
}

Object::Object(glm::vec3 position, glm::vec3 rotation, const char* textureLocation, const char* vertexLocation, const char* fragmentLocation)
{
	this->position = position;
	this->rotX = rotation.x;
	this->rotY = rotation.y;
	this->rotZ = rotation.z;
	this->totalVertices = 0;
	loadModel();
	loadShader(vertexLocation, fragmentLocation);
	loadTexture(textureLocation);
	createModelMatrix();
}

Object::~Object()
{
}

void Object::loadTexture(const char* textureLocation)
{
	this->texture = Texture(textureLocation);
}
void Object::loadTexture(Texture newTexture)
{
	this->texture = newTexture;
}
void Object::loadShader(const char* vertex, const char* fragment)
{
	this->shader = Shader(vertex, fragment);
}
void Object::loadModel()
{
	float cube[] = {
		// positions          // colors           // texture coords
		-1.0f,  -1.0f, 1.0f,   0.5f, 0.5f, 0.5f,   1.0f, 1.0f,   // top right front
		1.0f, -1.0f, 1.0f,   0.5f, 0.5f, 0.5f,   1.0f, 0.0f,   // bottom right front
		1.0f, 1.0f, 1.0f,   0.5f, 0.5f, 0.5f,   0.0f, 0.0f,   // bottom left front
		-1.0f,  1.0f, 1.0f,   0.5f, 0.5f, 0.5f,   0.0f, 1.0f,   // top left front
		-1.0f,  -1.0f, -1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right back
		1.0f, -1.0f, -1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right back
		1.0f, 1.0f, -1.0f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // bottom left back
		-1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 0.0f,   0.0f, 1.0f   // top left back
	};


	int cubeIndices[] = {
		//front face
		0, 1, 2,
		2, 3, 0,
		// right face
		1, 5, 6,
		6, 2, 1,
		// back face
		7, 6, 5,
		5, 4, 7,
		// left face
		4, 0, 3,
		3, 7, 4,
		// bottom face
		4, 5, 1,
		1, 0, 4,
		// top  face
		3, 2, 6,
		6, 7, 3
	};

	this->totalVertices = sizeof(cubeIndices) / sizeof(cubeIndices[0]);

	// Create new buffers and vertex arrays 
	glGenVertexArrays(1, &(this->VAO));
	glGenBuffers(1, &(this->VBO));
	glGenBuffers(1, &(this->EBO));

	// Cube VAO
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);


	// Set interpretation of vertex data in VBO - will apply to currently bound GL_ARRAY_BUFFER
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void Object::createModelMatrix()
{
	this->model = glm::mat4(1.0f);
	this->model = glm::translate(model, this->position);
	this->model = glm::rotate(model, glm::radians(this->rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	this->model = glm::rotate(model, glm::radians(this->rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	this->model = glm::rotate(model, glm::radians(this->rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
	
}

void Object::update(float dt, std::map<int, bool> &keys)
{
	/*if (keys[GLFW_KEY_W])
	{
		this->rotY -= 0.05;
	}

	if (keys[GLFW_KEY_A])
	{
		this->rotZ -= 0.05;
	}

	if (keys[GLFW_KEY_S])
	{
		this->rotY += 0.05;
	}

	if (keys[GLFW_KEY_D])
	{
		this->rotZ += 0.05;
	}

	if (keys[GLFW_KEY_Q])
	{
		this->rotX -= 0.05;
	}

	if (keys[GLFW_KEY_E])
	{
		this->rotX += 0.05;
	}*/

	createModelMatrix();
}

void Object::destroyObject()
{
	glDeleteTextures(1, &(this->texture.ID));
	glDeleteBuffers(1, &(this->VBO));
	glDeleteVertexArrays(1, &(this->VAO));
	glDeleteProgram(this->shader.ID);
	
}
