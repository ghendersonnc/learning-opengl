#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera {
private:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 front;
	glm::vec3 worldUp;
	float yaw;
	float pitch;
	float movementSpeed;
	float mouseSens;
	void updateCameraVectors();
public:
	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
		this->position = position;
		this->up = up;
		this->yaw = yaw;
		this->pitch = pitch;
		this->movementSpeed = 2.5f;
		this->mouseSens = 0.1f;
	}
	glm::mat4 getViewMat();
	
};
