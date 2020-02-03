
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <utility>

#include "GL/glew.h"
#include "GLM/glm.hpp"

#include "Enums.hpp"
#include "Texture.hpp"

#define PI 3.14159265358979323846

typedef std::pair<glm::vec3,glm::vec3> BB;

class Entity
{
public:

    ~Entity();

    void setMMLocation(GLuint MMLocation);
    glm::mat4 getMM() const;

    void draw();

protected:

    Entity();

    GLuint VAO;

    glm::vec3 position;
    glm::vec3 size;
    float rotX, rotY, rotZ;

    glm::vec3 origin;
    BB bb;
    
    bool MMOutOfDate;

    const Texture* texture;
    bool blending;

    static const glm::mat4 identity;

private:

    virtual void specificDraw() const = 0;

    void computeMM();

    GLuint MMLocation;
    glm::mat4 MM;
};

#endif