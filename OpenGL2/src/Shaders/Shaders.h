#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

using std::cout;
using std::cerr;
using std::endl;

class Shader {
private:
	std::string vertexShaderSource;
	std::string fragmentShaderSource;

public:
	unsigned int ID;
	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
	void use();
	void destroy();

};
