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

// Reads a given shader file
std::string readShaderFile(std::string pathToShader);

// Tells GPU to compile shader
unsigned int compileShader(unsigned int type, const std::string& source);

// Create a shader program
int createShaderProgram(const std::string& vertShader, const std::string& fragShader);
