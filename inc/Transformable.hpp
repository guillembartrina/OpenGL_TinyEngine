
#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include <utility>

#include "gl/glew.h"
#include "GLM/glm.hpp"

#include "Enums.hpp"

typedef std::pair<glm::vec3,glm::vec3> BB;

class Transformable
{
public:

    Transformable();
    ~Transformable();

    void setMMLocation(GLuint MMlocation);

    //const float* getMM() const;
    void bind() const;

protected:

    glm::vec3 center;
    BB bb;

    glm::mat4 MM;

private:
    
    GLuint MMlocation;
};

#endif