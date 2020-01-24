
#include "Transformable.hpp"

#include "GL/glew.h"

const glm::mat4 Transformable::identity = glm::mat4(1.0);

Transformable::Transformable()
{
    static_assert(SUL2D_MM == SUL3D_MM);
    MMlocation = SUL3D_MM;
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