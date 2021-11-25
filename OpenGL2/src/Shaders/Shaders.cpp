#include "Shaders.h"

Shader::Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath) {

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
            char* errorLog = new char[queryLen];

            glGetShaderInfoLog(id, queryLen, &queryLen, errorLog);
            cerr << "Failed to compile "
                << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                << " shader\n" 
                << errorLog 
                << endl;
            glDeleteShader(id);
            delete[] errorLog;
            return (unsigned int) 0;
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