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

class Camera
{
public:
	// Members
	glm::vec3 position;
	glm::vec3 target;
	//glm::vec3 direction;
	glm::vec3 up;

	glm::mat4 view;

	float speed;
	float pitch;
	float yaw;

	// Methods
	Camera();
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float speed);
	~Camera();

	void updateViewMatrix();
	void update(float dt, std::map<int, bool>& keys);

private:

};