
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

    ~Transformable();

    void setMMLocation(GLuint MMlocation);

    //const float* getMM() const;
    void bind() const;

protected:

    Transformable();
    
    glm::vec3 center;
    BB bb;

    glm::mat4 MM;

    static const glm::mat4 identity;

private:
    
    GLuint MMlocation;
};

#endif