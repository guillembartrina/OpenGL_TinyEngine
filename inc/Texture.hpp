
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include "GL/glew.h"

enum FBComponent
{
    FBComponent_Color,
    FBComponent_Depth,
    FBComponent_Stencil,
    FBComponent_NUM
};

class Texture
{
public:

    Texture(unsigned int W, unsigned int H, FBComponent component);
    Texture(const std::string& filename);
    ~Texture();

    int getW() const;
    int getH() const;
    FBComponent getComponent() const;

    void bind(GLenum texLoc = GL_TEXTURE0) const;

private:

    GLuint ID;
    int W, H;
    FBComponent component;
};

#endif