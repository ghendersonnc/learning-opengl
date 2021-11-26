#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class VBO {
private:
	unsigned int ID;
	GLenum target;
public:
	VBO(GLenum target, float* vertices, GLsizeiptr size, GLenum usage);

	void update(GLsizeiptr size, const void* vertices);
	void bind();
	void unbind();
	void destroy();
};