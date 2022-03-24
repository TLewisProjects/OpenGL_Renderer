#include "Camera.h"

Camera::Camera()
{
	this->position = glm::vec3(0.0f,0.0f,0.0f);
	this->target = glm::vec3(1.0f, 0.0f, 0.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);

	this->fpsMode = false;

	updateViewMatrix();
}

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float speed, bool fpsMode)
{
	this->position = position;
	this->target = target;
	this->up = up;
	this->speed = speed;
	this->fpsMode = fpsMode;

	updateViewMatrix();
}

Camera::~Camera()
{
}

void Camera::updateViewMatrix() 
{
	this->view = glm::mat4(1.0f);
	this->view = glm::lookAt(this->position, this->target, this->up);

	//std::cout << glm::to_string(glm::lookAt(this->position, this->target, this->up)) << std::endl;
}

void Camera::update(float dt, std::map<int, bool>& keys)
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	this->target = this->position + direction;
	direction = glm::normalize(this->position - this->target);

	if (fpsMode)
	{
		direction.y = 0.0f;
	}

	if (keys[GLFW_KEY_W])
	{
		this->position -= dt *speed * glm::normalize(direction);
	}

	if (keys[GLFW_KEY_A])
	{
		this->position += glm::normalize(glm::cross(direction, this->up)) * this->speed * dt;
	}

	if (keys[GLFW_KEY_S])
	{
		this->position += dt * speed * glm::normalize(direction);
	}

	if (keys[GLFW_KEY_D])
	{
		this->position -= glm::normalize(glm::cross(direction, this->up)) * this->speed * dt;
	}

	this->updateViewMatrix();
}