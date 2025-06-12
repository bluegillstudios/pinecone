#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h> // or GLEW if used

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    Load(vertexPath, fragmentPath);
}

Shader::~Shader() {
    if (rendererID != 0) {
        glDeleteProgram(rendererID);
    }
}

bool Shader::Load(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexSource = ParseShader(vertexPath);
    std::string fragmentSource = ParseShader(fragmentPath);

    rendererID = CreateShader(vertexSource, fragmentSource);
    return rendererID != 0;
}

void Shader::Bind() const {
    glUseProgram(rendererID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& name) {
    if (uniformLocationCache.find(name) != uniformLocationCache.end())
        return uniformLocationCache[name];

    int location = glGetUniformLocation(rendererID, name.c_str());
    if (location == -1)
        std::cerr << "[Warning] Uniform '" << name << "' doesn't exist or is not used." << std::endl;

    uniformLocationCache[name] = location;
    return location;
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniform1i(const std::string& name, int value) {
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value) {
    glUniform1f(GetUniformLocation(name), value);
}

std::string Shader::ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    if (!stream.is_open()) {
        std::cerr << "[Error] Could not open shader file: " << filepath << std::endl;
        return "";
    }

    std::stringstream ss;
    ss << stream.rdbuf();
    return ss.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "[Error] Shader compilation failed:\n" << infoLog << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    if (vs == 0) {
        glDeleteProgram(program);
        return 0;
    }

    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    if (fs == 0) {
        glDeleteShader(vs);
        glDeleteProgram(program);
        return 0;
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "[Error] Shader linking failed:\n" << infoLog << std::endl;

        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(program);
        return 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
