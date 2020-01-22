
#ifndef MODEL3D_HPP
#define MODEL3D_HPP

#include "GL/glew.h"
#include "GLM/glm.hpp"

#include "Drawable.hpp"
#include "Transformable3D.hpp"
#include "IO.hpp"
#include "Enums.hpp"


class Model3D : public Drawable, public Transformable3D
{
public:

    Model3D(const DrawableDefinition& dd);
    ~Model3D();

    void draw() const;

private:

    GLuint VAO;
    std::vector<GLuint> VBOs;

    bool indexed;
    unsigned int elements;

    static BB computeBB(const DrawableDefinition& dd);

};

#endif