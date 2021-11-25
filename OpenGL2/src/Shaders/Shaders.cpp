#include "Shaders.h"

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
    {
        std::ifstream vertCode(vertexShaderPath);
        auto ss = std::ostringstream{};

        if (!vertCode.is_open()) {
            cerr << "Cannot open shader file" << endl;;
            exit(-1);
        }
        ss << vertCode.rdbuf();
        vertCode.close();
        this->vertexShaderSource = ss.str();
    }

    {
        std::ifstream fragCode(fragmentShaderPath);
        auto ss = std::ostringstream{};

        if (!fragCode.is_open()) {
            cerr << "Cannot open shader file" << endl;;
            exit(-1);
        }
        ss << fragCode.rdbuf();
        fragCode.close();
        this->fragmentShaderSource = ss.str();
    }
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    {
        const char* vSrc = this->vertexShaderSource.c_str();
        glShaderSource(vertexShader, 1, &vSrc, nullptr);
        glCompileShader(vertexShader);
        int result;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

        if (!result) {
            int queryLen;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &queryLen);
            char* errorLog = new char[queryLen];

            glGetShaderInfoLog(vertexShader, queryLen, &queryLen, errorLog);
            cerr << "Failed to compile vertex shader" << endl;
            glDeleteShader(vertexShader);

            delete[] errorLog;
        }
    }


    {
        const char* fSrc = this->fragmentShaderSource.c_str();
        glShaderSource(fragmentShader, 1, &fSrc, nullptr);
        glCompileShader(fragmentShader);
        int result;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

        if (!result) {
            int queryLen;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &queryLen);
            char* errorLog = new char[queryLen];

            glGetShaderInfoLog(fragmentShader, queryLen, &queryLen, errorLog);
            cerr << "Failed to compile fragment shader" << endl;
            glDeleteShader(fragmentShader);

            delete[] errorLog;
        }
    }

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);
    glLinkProgram(this->ID);
    glValidateProgram(this->ID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
     
    int valid;

    glGetProgramiv(this->ID, GL_VALIDATE_STATUS, &valid);

    if (valid == GL_FALSE) {
        cerr << "Shader programmed failed validation. Shader program will NOT execute." << endl;
    }

}

void Shader::use() {
    glUseProgram(this->ID);
}

void Shader::destroy() {
    glDeleteProgram(this->ID);
}