#include "model.h"
#include "Render.h"
#include "Shader.h"

#include <iostream>

Model::Model(const std::string& path) {
    LoadModel(path);
}

void Model::Draw(const Renderer& renderer, const Shader& shader,
                 const glm::mat4& modelMatrix,
                 const glm::mat4& viewMatrix,
                 const glm::mat4& projectionMatrix) {
    for (auto& mesh : meshes) {
        renderer.DrawMesh(mesh, shader, modelMatrix, viewMatrix, projectionMatrix);
    }
}

void Model::LoadModel(const std::string& path) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "[Assimp Error] " << importer.GetErrorString() << std::endl;
        return;
    }

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;

        vertex.Position[0] = mesh->mVertices[i].x;
        vertex.Position[1] = mesh->mVertices[i].y;
        vertex.Position[2] = mesh->mVertices[i].z;

        vertex.Normal[0] = mesh->mNormals[i].x;
        vertex.Normal[1] = mesh->mNormals[i].y;
        vertex.Normal[2] = mesh->mNormals[i].z;

        if (mesh->mTextureCoords[0]) {
            vertex.TexCoords[0] = mesh->mTextureCoords[0][i].x;
            vertex.TexCoords[1] = mesh->mTextureCoords[0][i].y;
        } else {
            vertex.TexCoords[0] = 0.0f;
            vertex.TexCoords[1] = 0.0f;
        }

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh(vertices, indices);
}