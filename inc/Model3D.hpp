
#ifndef MODEL3D_HPP
#define MODEL3D_HPP

#include "GL/glew.h"
#include "GLM/glm.hpp"

#include "Drawable.hpp"
#include "Transformable3D.hpp"
#include "IO.hpp"
#include "Enums.hpp"
#include "Texture.hpp"


class Model3D : public Drawable, public Transformable3D
{
public:

    Model3D(const DrawableDefinition& dd);
    ~Model3D();

    void draw() const;

    static Model3D* plane();
    static Model3D* cube();

private:

    GLuint VAO;
    std::vector<GLuint> VBOs;

    bool indexed;
    unsigned int elements;

    Texture* texture;

    static BB computeBB(const DrawableDefinition& dd);
};

#endif