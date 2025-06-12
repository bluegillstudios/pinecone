#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader {
public:
    Shader() = default;
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Load and compile shaders from files
    bool Load(const std::string& vertexPath, const std::string& fragmentPath);

    // Uniform setters
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);

private:
    unsigned int rendererID = 0;

    // Cache for uniform locations
    std::unordered_map<std::string, int> uniformLocationCache;

    int GetUniformLocation(const std::string& name);
    std::string ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};
