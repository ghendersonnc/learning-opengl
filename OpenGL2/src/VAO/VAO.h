#pragma once
#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "VBO/VBO.h"

class VAO {
private:
	unsigned int ID;
public:
	VAO();
	void bind();
	void linkVBO(VBO& vbo, const unsigned int index, int size);
	void unbind();
	void destroy();
};