#pragma once

#include <vector>
#include <GL/glew.h>  

struct Vertex {
    float Position[3];
    float Normal[3];
    float TexCoords[2];
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Bind() const;
    void Unbind() const;

    unsigned int GetIndexCount() const { return static_cast<unsigned int>(indicesCount); }

private:
    unsigned int VAO, VBO, EBO;
    size_t indicesCount;

    void SetupMesh();
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};
