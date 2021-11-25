#include "Shaders.h"

std::string readShaderFile(std::string pathToShader) {
    std::ifstream shaderCode(pathToShader);
    auto ss = std::ostringstream{};

    if (!shaderCode.is_open()) {
        cerr << "Cannot open shader file" << endl;;
        exit(-1);
    }

    ss << shaderCode.rdbuf();
    shaderCode.close();
    return ss.str();
}

unsigned int compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    // "Handle" shaders not compiling
    if (!result) {
        int queryLen;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &queryLen);
        char* errorLog = new char[queryLen];

        glGetShaderInfoLog(id, queryLen, &queryLen, errorLog);
        cerr << "Failed to compile "
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader" << endl;;
        cerr << errorLog << endl;;
        glDeleteShader(id);

        delete[] errorLog;

        return 0;
    }

    return id;
}

int createShaderProgram(const std::string& vertShader, const std::string& fragShader) {
    unsigned int shaderProgram = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragShader);

    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return shaderProgram;
}