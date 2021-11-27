#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &this->ID);
	glBindVertexArray(this->ID);
}
void VAO::bind() {
	glBindVertexArray(this->ID);
}
void VAO::linkVBO(VBO& vbo, const unsigned int index, int size) {
	vbo.bind();
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)0);

	vbo.unbind();
}
void VAO::unbind() {
	glBindVertexArray(0);
}

void VAO::destroy() {
	glDeleteVertexArrays(1, &this->ID);
}