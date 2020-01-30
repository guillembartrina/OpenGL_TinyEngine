
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <utility>

#include "GL/glew.h"
#include "GLM/glm.hpp"

#include "Enums.hpp"
#include "Texture.hpp"

typedef std::pair<glm::vec3,glm::vec3> BB;

class Entity
{
public:

    ~Entity();

    void setMMLocation(GLuint MMlocation);

    void draw() const;

protected:

    Entity();

    const Texture* texture;
    GLuint VAO;

    glm::vec3 center;
    glm::vec3 up;
    BB bb;

    glm::vec3 origin;
    glm::mat4 MM;

    static const glm::mat4 identity;

private:

    virtual void specificDraw() const = 0;

    GLuint MMlocation;
};

#endif