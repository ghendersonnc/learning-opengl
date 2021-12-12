#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "GL/glew.h"
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
    Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath) {
        auto readShader = [](const std::string shaderPath) {
            std::ifstream shaderCode(shaderPath);
            auto ss = std::ostringstream{};

            if (!shaderCode.is_open()) {
                cerr << "Cannot open (" << shaderPath << "): file does not exist" << endl;;
            }
            ss << shaderCode.rdbuf();
            shaderCode.close();
            return ss.str();
        };
        this->vertexShaderSource = readShader(vertexShaderPath);
        this->fragmentShaderSource = readShader(fragmentShaderPath);

        unsigned int vertexShader;
        unsigned int fragmentShader;

        auto compileShader = [](GLenum type, const std::string shaderSource) {
            const char* source = shaderSource.c_str();
            unsigned int id = glCreateShader(type);
            glShaderSource(id, 1, &source, nullptr);
            glCompileShader(id);

            int result;
            glGetShaderiv(id, GL_COMPILE_STATUS, &result);

            if (result == GL_FALSE) {
                int queryLen;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &queryLen);
                char* errorLog = (char*)malloc(queryLen * sizeof(char));

                glGetShaderInfoLog(id, queryLen, &queryLen, errorLog);
                cerr << "Failed to compile "
                    << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                    << " shader\n"
                    << errorLog
                    << endl;

                free(errorLog);

                glDeleteShader(id);
                return (unsigned int)0;
            }

            return id;
        };

        vertexShader = compileShader(GL_VERTEX_SHADER, this->vertexShaderSource);
        fragmentShader = compileShader(GL_FRAGMENT_SHADER, this->fragmentShaderSource);

        this->ID = glCreateProgram();
        glAttachShader(this->ID, vertexShader);
        glAttachShader(this->ID, fragmentShader);
        glLinkProgram(this->ID);
        glValidateProgram(this->ID);

        // Cleanup
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        int valid;

        glGetProgramiv(this->ID, GL_VALIDATE_STATUS, &valid);

        // Kindly let the dev know shaders didn't work
        if (valid == GL_FALSE) {
            cerr << "Shader programmed failed validation. Shader program will NOT execute." << endl;
        }

    }

    void use() {
        glUseProgram(this->ID);
    }

    void setVec3(const char* uniformName, const glm::vec3& vector) {
        glUniform3fv(glGetUniformLocation(this->ID, uniformName), 1, glm::value_ptr(vector));
    }

    void setVec4(const char* uniformName, const glm::vec4& vector) {
        glUniform4fv(glGetUniformLocation(this->ID, uniformName), 1, glm::value_ptr(vector));
    }

    void setMat4(const char* uniformName, glm::mat4& matrix) {
        glUniformMatrix4fv(glGetUniformLocation(this->ID, uniformName), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void destroy() {
        glDeleteProgram(this->ID);
    }

};
