#include "App.h"
#include "Shader.h"

App::App()
{
}

App::~App()
{
	
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

void App::setupObjects()
{
	this->cube1 = Object(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 45.0f), "resources/textures/grass_grass_0131_01_s.jpg", "src/vertex.glsl", "src/fragment.glsl");
};