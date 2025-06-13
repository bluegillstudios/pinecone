#pragma once

#include <string>
#include <GL/glew.h>  

class Texture {
public:
    Texture() = default;
    Texture(const std::string& path, bool flipVertically = true);

    void Bind(unsigned int unit = 0) const;
    void Unbind() const;
    void Delete();

    unsigned int GetID() const { return ID; }

private:
    unsigned int ID = 0;
    int width = 0, height = 0, channels = 0;
};