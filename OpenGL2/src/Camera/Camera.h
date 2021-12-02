#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera {
private:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 left;
public:
	Camera();
};
