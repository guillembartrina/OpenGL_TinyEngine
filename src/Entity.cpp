
#include "Entity.hpp"

#include "GLM/gtc/matrix_transform.hpp"

#include "Program.hpp"

const glm::mat4 Entity::identity = glm::mat4(1.0);

Entity::Entity()
{
    static_assert(SUL2D_MM == SUL3D_MM);
    static_assert(SUL2D_textured == SUL3D_textured);
    MMLocation = SUL2D_MM;

    position = glm::vec3(0.0);
    size = glm::vec3(1.0);
    rotX = rotY = rotZ = 0.f;

    origin = glm::vec3(0.0);
    //bb?

    MMOutOfDate = false;
    MM = glm::mat4(1.0);

    texture = nullptr;
    blending = false;
}

Entity::~Entity() {}

void Entity::setMMLocation(GLuint MMLocation)
{
    this->MMLocation = MMLocation;
}

glm::mat4 Entity::getMM()
{
    if(MMOutOfDate)
    {
        computeMM();
        MMOutOfDate = false;
    }

    return MM;
}

void Entity::draw()
{
    if(MMOutOfDate)
    {
        computeMM();
        MMOutOfDate = false;
    }

    //FIX
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if(blending) glEnable(GL_BLEND);
    else glDisable(GL_BLEND);
    
    glBindVertexArray(VAO);
    Program::getActiveProgram()->setUniformValue(MMLocation, MM);
    Program::getActiveProgram()->setUniformValue(SUL2D_textured, (texture ? GL_TRUE : GL_FALSE));
    if(texture) texture->bind();
    specificDraw();
    glBindVertexArray(0);
}

void Entity::computeMM()  //OBJ -> centerto000 -> scale -> originto000 -> rotates -> origintoposition 
{
    MM = identity;
    MM = glm::translate(MM, position);
    MM = glm::rotate(MM, rotZ, glm::vec3(0.0, 0.0, 1.0));
    MM = glm::rotate(MM, rotY, glm::vec3(0.0, 1.0, 0.0));
    MM = glm::rotate(MM, rotX, glm::vec3(1.0, 0.0, 0.0));
    MM = glm::translate(MM, -origin);
    MM = glm::scale(MM, size/(bb.second-bb.first));
    MM = glm::translate(MM, -(bb.first+bb.second)/2.f);
}