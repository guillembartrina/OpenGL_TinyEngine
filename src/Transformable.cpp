
#include "Transformable.hpp"

#include "GL/glew.h"

Transformable::Transformable()
{
    MMlocation = SUL::MM;
}

Transformable::~Transformable() {}

void Transformable::setMMLocation(GLuint MMlocation)
{
    this->MMlocation = MMlocation;
}

/*
const float* Transformable::getMM() const
{
    return &MM[0][0];
}
*/

void Transformable::bind() const
{
    glUniformMatrix4fv(MMlocation, 1, GL_FALSE, &MM[0][0]);
}