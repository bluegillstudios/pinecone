#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include "Mesh.h"

class Renderer {
public:
    Renderer();

    // Set the clear color for the screen
    void SetClearColor(const glm::vec4& color);

    // Clear the color and depth buffers
    void Clear();

    // Draw a mesh using a given shader and model transform
    void DrawMesh(const Mesh& mesh, const Shader& shader, const glm::mat4& modelMatrix,
                  const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    
private:
    glm::vec4 clearColor;
};