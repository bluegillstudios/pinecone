#include "Renderer.h"
#include <GL/glew.h> 

Renderer::Renderer()
    : clearColor(0.1f, 0.1f, 0.1f, 1.0f) // Default dark gray
{
}

void Renderer::SetClearColor(const glm::vec4& color) {
    clearColor = color;
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawMesh(const Mesh& mesh, const Shader& shader,
                        const glm::mat4& modelMatrix,
                        const glm::mat4& viewMatrix,
                        const glm::mat4& projectionMatrix)
{
    shader.Bind();

    // Set shader uniforms (model/view/projection matrices)
    shader.SetUniformMat4f("u_Model", modelMatrix);
    shader.SetUniformMat4f("u_View", viewMatrix);
    shader.SetUniformMat4f("u_Projection", projectionMatrix);

    mesh.Bind();
    glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
    mesh.Unbind();

    shader.Unbind();
}