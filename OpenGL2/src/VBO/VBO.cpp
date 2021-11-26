#include "VBO.h"

VBO::VBO(GLenum target, float* vertices, GLsizeiptr size, GLenum usage) {
	this->target = target;

	glGenBuffers(1, &this->ID);
	glBindBuffer(this->target, this->ID);
	glBufferData(target, size, vertices, usage);
}

void VBO::update(GLsizeiptr size, const void* vertices) {
	glBufferSubData(this->target, 0, size, vertices);
}

void VBO::bind() {
	glBindBuffer(this->target, this->ID);
}
void VBO::unbind() {
	glBindBuffer(this->target, 0);
}
void VBO::destroy() {
	glDeleteBuffers(1, &this->ID);
}