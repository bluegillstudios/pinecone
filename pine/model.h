#pragma once

#include <string>
#include <vector>

#include "Mesh.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

class Renderer;
class Shader;

class Model {
public:
    Model() = default;
    Model(const std::string& path);

    void Draw(const Renderer& renderer, const Shader& shader,
              const glm::mat4& modelMatrix,
              const glm::mat4& viewMatrix,
              const glm::mat4& projectionMatrix);

private:
    std::vector<Mesh> meshes;

    void LoadModel(const std::string& path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
};