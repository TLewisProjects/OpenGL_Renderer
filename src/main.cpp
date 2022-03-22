#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// STL
#include <map>
#include <vector>

#include "App.h"

#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void catchInput(GLFWwindow* window, std::map<int, bool>& keys);

int main()
{
	App app = App();

	std::map<int, bool> keys;

	for (int i = 0; i < 351; i++)
	{
		keys[i] = false;
	}

	glfwInit();

	if (app.initializeWindow() == -1)
	{
		return -1;
	}
	
	glfwMakeContextCurrent(app.window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
	glfwSetFramebufferSizeCallback(app.window, framebuffer_size_callback);

	app.setupObjects();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(app.window))
	{
		// Input
		catchInput(app.window, keys);

		if (keys[GLFW_KEY_ESCAPE])
		{
			glfwSetWindowShouldClose(app.window, true);
		}

		// Update objects
		app.cube1.update(keys);

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(app.cube1.shader.ID);
		float timeValue = glfwGetTime();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, app.cube1.texture.ID);

		app.cube1.shader.setInt("ourTexture", 0);
		glBindVertexArray(app.cube1.VAO);

		// create transformation matrix
		glm::mat4 model = app.cube1.model;

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		app.cube1.shader.setMat4("model", model);
		app.cube1.shader.setMat4("view", view);
		app.cube1.shader.setMat4("projection", projection);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(0));

		// Swap buffers
		glfwPollEvents();
		glfwSwapBuffers(app.window);
	}

	app.cube1.destroyObject();

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void catchInput(GLFWwindow* window, std::map<int, bool> &keys)
{
	// Construct vector from array for ease of iteration
	int keysToCheck[] = { GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_Q, GLFW_KEY_E };
	std::vector<int> keysVector(keysToCheck, keysToCheck + sizeof(keysToCheck) / sizeof(int));

	for (int i : keysVector)
	{
		if (glfwGetKey(window, i) == GLFW_PRESS)
		{
			keys[i] = true;
		}
		else if (glfwGetKey(window, i) == GLFW_RELEASE)
		{
			keys[i] = false;
		}
	}

}

void processInput(std::map<int, bool>& keys)
{
	if (keys[GLFW_KEY_W])
	{

	}

	if (keys[GLFW_KEY_A])
	{

	}

	if (keys[GLFW_KEY_S])
	{

	}

	if (keys[GLFW_KEY_D])
	{

	}
}