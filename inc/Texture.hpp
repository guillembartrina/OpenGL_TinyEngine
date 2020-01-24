
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include "GL/glew.h"

class Texture
{
public:

    Texture(const std::string& filename);
    ~Texture();

    void bind() const;

private:

    GLuint ID;
    int W, H;
};

#endif