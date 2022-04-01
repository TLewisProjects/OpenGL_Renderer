#include "App.h"

App::App()
{

};

App::App(int width, int height)
{
	this->width = width;
	this->height = height;

	if (this->initializeWindow(this->width, this->height) == -1)
	{
		throw std::exception("Window failed to initialise");
	}

	this->lastMousePos = glm::vec2(0.5f * this->width, 0.5f * this->height);
	this->firstMouse = true;
	glfwSetWindowUserPointer(window, this);
};

App::~App()
{

};

int App::initializeWindow(int width, int height) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(width, height, "OpenGL_Renderer", NULL, NULL);
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
	//this->cube1 = Object(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 45.0f), "resources/textures/grass_grass_0131_01_s.jpg", "src/vertex.glsl", "src/fragment.glsl");

	//for (int i = 0; i < 1; i++)
	//{
	//	this->cubes.push_back(Object(glm::vec3((i * 3.0f) - 9.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 45.0f), "resources/textures/grass_grass_0131_01_s.jpg", "src/vertex.glsl", "src/fragment.glsl"));
	//}
	this->cubes.push_back(Object(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 45.0f), "resources/textures/grass_grass_0131_01_s.jpg", "src/vertex.glsl", "src/fragment.glsl"));
};

void App::setupCamera()
{
	this->camera = Camera(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 2.5f, false);
};