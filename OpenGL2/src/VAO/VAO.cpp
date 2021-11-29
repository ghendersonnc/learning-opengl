#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &this->ID);
	glBindVertexArray(this->ID);
}
void VAO::bind() {
	glBindVertexArray(this->ID);
}
void VAO::linkVBO(VBO& vbo, const unsigned int index, const int size, const int stride, const int offset) {
	vbo.bind();
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(index);

	vbo.unbind();
}
void VAO::unbind() {
	glBindVertexArray(0);
}

void VAO::destroy() {
	glDeleteVertexArrays(1, &this->ID);
}