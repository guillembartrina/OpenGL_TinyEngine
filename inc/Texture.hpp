
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include "GL/glew.h"

enum TextureComponent
{
    TextureComponent_Color,
    TextureComponent_Depth,
    TextureComponent_Stencil,
    TextureComponent_NUM
};

class Texture
{
public:

    Texture(unsigned int W, unsigned int H, TextureComponent component);
    Texture(const std::string& filename);
    ~Texture();

    int getW() const;
    int getH() const;
    TextureComponent getComponent() const;

    void bind(GLenum texLoc = GL_TEXTURE0) const;

private:

    GLuint ID;
    int W, H;
    TextureComponent component;
};

#endif