#include "App.h"
#include "Shader.h"

App::App()
{
}

App::~App()
{
	glDeleteVertexArrays(1, &(this->VAO1));
	glDeleteVertexArrays(1, &(this->VAO2));
	glDeleteVertexArrays(1, &(this->VAO3));

	glDeleteProgram(this->shaderProgram1.ID);
	glDeleteProgram(this->shaderProgram2.ID);
}

int App::initializeWindow() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint();

	this->window = glfwCreateWindow(800, 600, "OpenGL_Renderer", NULL, NULL);

	if (this->window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();

		return -1;
	}
	return 0;
};

void App::setupVertexBuffers() {
	//Set up vertices in a vertex buffer object
	float triangle1[] = {
			-0.5f, 0.0f, 0.0f,
			0.5f, -0.5, 0.0f,
			0.0f, 0.5f, 0.0f
	};

	float triangle2[] = {
			0.5f, 0.5f, 0.0f, 1.0f, 0.0f,0.0f, 0.0f, 0.0f,
			0.75f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			0.75f, 0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
	};

	float triangle3[] = {
		// positions          // colors           // texture coords
		-0.65f,  0.9f, 0.0f,   0.5f, 0.5f, 0.5f,   0.5f, 0.5f,   // top right front
		-0.65f, 0.65f, 0.0f,   0.5f, 0.5f, 0.5f,   0.5f, 0.0f,   // bottom right front
		-0.9f, 0.65f, 0.0f,   0.5f, 0.5f, 0.5f,   0.0f, 0.0f,   // bottom left front
	};

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

	glGenVertexArrays(1, &(this->VAO1));
	glGenVertexArrays(1, &(this->VAO2));
	glGenVertexArrays(1, &(this->VAO3));

	glGenBuffers(1, &(this->VBO1));
	glGenBuffers(1, &(this->VBO2));
	glGenBuffers(1, &(this->VBO3));

	glGenBuffers(1, &(this->EBO1));

	glBindVertexArray(this->VAO1);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO1); // Any function calls related to buffers will now target this VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
	// Set interpretation of vertex data in VBO - will apply to currently bound GL_ARRAY_BUFFER
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(this->VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);

	// Set interpretation of vertex data in VBO - will apply to currently bound GL_ARRAY_BUFFER
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Cube VAO
	glBindVertexArray(this->VAO3);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);


	// Set interpretation of vertex data in VBO - will apply to currently bound GL_ARRAY_BUFFER
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

};

void App::setupShaderProgram()
{
	this->shaderProgram1 = Shader("src/vertex.glsl", "src/fragment.glsl");
	this->shaderProgram2 = Shader("src/vertexMultiColor.glsl", "src/fragmentMultiColor.glsl");
}

void App::loadTexture(const char* textureFile) 
{
	this->texture1 = Texture(textureFile);
}