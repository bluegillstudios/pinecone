#include "Model.h"
#include "Renderer.h"
#include "Shader.h"
#include <iostream>

Model::Model(const std::string& path) {
    LoadModel(path);
}

void Model::Draw(const Renderer& renderer, const Shader& shader,
                 const glm::mat4& modelMatrix,
                 const glm::mat4& viewMatrix,
                 const glm::mat4& projectionMatrix)
{
    for (auto& mesh : meshes) {
        renderer.DrawMesh(mesh, shader, modelMatrix, viewMatrix, projectionMatrix);
    }
}

void Model::LoadModel(const std::string& path) {
    // For now, this is a stub.
    // Later we can integrate Assimp or write an OBJ loader.

    std::cerr << "[Warning] Model loading not yet implemented: " << path << std::endl;
}

void Model::ProcessNode(void* node) {
    // Stub
}

Mesh Model::ProcessMesh(void* mesh) {
    // Stub
    return Mesh({}, {});
}