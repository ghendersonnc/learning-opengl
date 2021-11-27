#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


using std::cout;
using std::cerr;
using std::endl;

class Shader {
private:
	std::string vertexShaderSource;
	std::string fragmentShaderSource;

public:
	unsigned int ID;
	Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath);
	void use();
	void setMat4Uniform(const char* uniformName, glm::mat4 matrix);
	void destroy();

};
