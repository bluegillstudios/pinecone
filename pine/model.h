#pragma once

#include <vector>
#include <string>
#include "Mesh.h"
#include "Texture.h"

class Model {
public:
    Model() = default;
    Model(const std::string& path);

    void Draw(const class Renderer& renderer, const class Shader& shader,
              const glm::mat4& modelMatrix,
              const glm::mat4& viewMatrix,
              const glm::mat4& projectionMatrix);

private:
    std::vector<Mesh> meshes;
    std::vector<Texture> texturesLoaded; // To avoid loading duplicates

    void LoadModel(const std::string& path);
    void ProcessNode(void* node); // placeholder, to be implemented depending on loader
    Mesh ProcessMesh(void* mesh); // placeholder

    // We can use Assimp or write our own model loading.
};
