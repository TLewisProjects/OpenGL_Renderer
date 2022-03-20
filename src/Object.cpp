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
}

Object::Object(glm::vec3 position, glm::vec3 rotation, const char* textureLocation, const char* vertexLocation, const char* fragmentLocation)
{
	this->position = position;
	this->rotX = rotation.x;
	this->rotY = rotation.y;
	this->rotZ = rotation.z;
	loadModel();
	loadShader(vertexLocation, fragmentLocation);
	loadTexture(textureLocation);
}

Object::~Object()
{
	glDeleteTextures(1, &(this->texture.ID));
	glDeleteVertexArrays(1, &(this->VAO));
	glDeleteBuffers(1, &(this->VBO));
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
		-0.65f,  0.9f, 0.0f,   0.5f, 0.5f, 0.5f,   1.0f, 1.0f,   // top right front
		-0.65f, 0.65f, 0.0f,   0.5f, 0.5f, 0.5f,   1.0f, 0.0f,   // bottom right front
		-0.9f, 0.65f, 0.0f,   0.5f, 0.5f, 0.5f,   0.0f, 0.0f,   // bottom left front
		-0.9f,  0.9f, 0.0f,   0.5f, 0.5f, 0.5f,   0.0f, 1.0f,   // top left front
		-0.65f,  0.9f, -0.25f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right back
		-0.65f, 0.65f, -0.25f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right back
		-0.9f, 0.65f, -0.25f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // bottom left back
		-0.9f,  0.9f, -0.25f,    1.0f, 1.0f, 0.0f,   0.0f, 1.0f   // top left back
	};


	int cubeIndices[] = {
		0, 1, 2,
		2, 3, 0,
		3, 4, 5,
		3, 5, 0,
		0, 5, 1,
		1, 6, 5,
		4, 5, 6,
		6, 7, 4,
		1, 2, 6,
		6, 2, 7,
		6, 1, 2,
		2, 7, 6
	};

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
	this->model = glm::rotate(model, glm::radians(this->rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	this->model = glm::rotate(model, glm::radians(this->rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	this->model = glm::rotate(model, glm::radians(this->rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
	this->model = glm::translate(model, this->position);
}
