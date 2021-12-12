#pragma once
#include <iostream>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "VBO.h"

class VAO {
private:
	unsigned int ID;
public:
	VAO() {
		glGenVertexArrays(1, &this->ID);
		glBindVertexArray(this->ID);
	}
	void bind() {
		glBindVertexArray(this->ID);
	}
	void linkVBO(VBO& vbo, const unsigned int index, const int size, const int stride, const int offset) {
		vbo.bind();
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(index);

		vbo.unbind();
	}
	void unbind() {
		glBindVertexArray(0);
	}
	void destroy() {
		glDeleteVertexArrays(1, &this->ID);
	}
};