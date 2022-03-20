#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "App.h"

#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	App app = App();

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

	app.setupVertexBuffers();
	app.setupShaderProgram();

	app.loadTexture("resources/textures/wall.jpg");

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(app.window))
	{
		// Input
		processInput(app.window);

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(app.shaderProgram1.ID);
		float timeValue = glfwGetTime();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, app.texture1.ID);

		app.shaderProgram1.setInt("ourTexture", 0);
		glBindVertexArray(app.VAO3);

		// create transformation matrix
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		app.shaderProgram1.setMat4("model", model);
		app.shaderProgram1.setMat4("view", view);
		app.shaderProgram1.setMat4("projection", projection);

		// create rotation matrix
		float rotValue = asin(sin(timeValue));
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, rotValue, glm::vec3(1.0, 0.0, 0.0));
		app.shaderProgram1.setMat4("transform", trans);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(0));

		glUseProgram(app.shaderProgram2.ID);
		app.shaderProgram2.setInt("ourTexture", 0);
		glBindVertexArray(app.VAO2);
		float offsetY = (sin(timeValue) * 0.2f);
		app.shaderProgram2.setVec3("offset", 0.2f, offsetY, 0.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


		// Swap buffers
		glfwPollEvents();
		glfwSwapBuffers(app.window);
	}

	glDeleteTextures(1, &(app.texture1.ID));

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}