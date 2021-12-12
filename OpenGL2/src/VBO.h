#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class VBO {
private:
	unsigned int ID;
	GLenum target;
public:
	VBO(GLenum target, float* vertices, GLsizeiptr size, GLenum usage) {
		this->target = target;

		glGenBuffers(1, &this->ID);
		glBindBuffer(this->target, this->ID);
		glBufferData(target, size, vertices, usage);
	}

	void update(GLsizeiptr size, const void* vertices) {
		glBufferSubData(this->target, 0, size, vertices);
	}

	void bind() {
		glBindBuffer(this->target, this->ID);
	}
	void unbind() {
		glBindBuffer(this->target, 0);
	}
	void destroy() {
		glDeleteBuffers(1, &this->ID);
	}
};