
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "GL/glew.h"
#include "GLM/glm.hpp"

#include "Enums.hpp"
#include "Texture.hpp"

class Entity
{
public:

    ~Entity();

    void setMMLocation(GLuint MMLocation);
    glm::mat4 getMM(); //Not const 'cause modify MM

    void draw(); //Not const 'cause modify MM

protected:

    Entity();

    GLuint VAO;

    glm::vec3 position;
    glm::vec3 size;
    float rotX, rotY, rotZ;

    glm::vec3 origin;
    BB bb;
    
    bool MMOutOfDate;

    const Texture* texture; //only a reference, it has to be deleted at origin
    bool blending;

    static const glm::mat4 identity;

private:

    virtual void specificDraw() const = 0;

    void computeMM();

    GLuint MMLocation;
    glm::mat4 MM;
};

#endif