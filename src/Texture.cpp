
#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

#include <iostream>

Texture::Texture(unsigned int W, unsigned int H, FBComponent component)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    switch(component)
    {
        case FBComponent_Color:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
            break;
        case FBComponent_Depth:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, W, H, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
            break;
        case FBComponent_Stencil:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_STENCIL, W, H, 0, GL_DEPTH_STENCIL, GL_FLOAT, 0);
            break;
    }

    this->W = W;
    this->H = H;
    this->component = component;
}

Texture::Texture(const std::string& filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int nrc;
    
    unsigned char* data = stbi_load(filename.c_str(), &W, &H, &nrc, 4);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        std::cerr << "Texture: error loading" << std::endl;
    }
    stbi_image_free(data);

    component = FBComponent_Color;

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

int Texture::getW() const
{
    return W;
}

int Texture::getH() const
{
    return H;
}

FBComponent Texture::getComponent() const
{
    return component;
}

void Texture::bind(GLenum texLoc) const
{
    glActiveTexture(texLoc);
    glBindTexture(GL_TEXTURE_2D, ID);
}