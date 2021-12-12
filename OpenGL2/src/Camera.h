#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera {
private:
	float yaw;
	float pitch;
	float movementSpeed;
	float mouseSens;
	void updateCameraVectors();
public:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 front;
	glm::vec3 worldUp;

	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
		this->position = position;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;
		this->movementSpeed = 2.5f;
		this->mouseSens = 0.1f;
		
		this->front = glm::vec3(
			cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),
			sin(glm::radians(this->pitch)),
			sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch))
		);

		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
		
	}
	glm::mat4 getViewMat();
	
};
