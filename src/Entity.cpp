
#include "Entity.hpp"

const glm::mat4 Entity::identity = glm::mat4(1.0);

Entity::Entity()
{
    static_assert(SUL2D_MM == SUL3D_MM);
    static_assert(SUL2D_textured == SUL3D_textured);
    MMlocation = SUL2D_MM;
    up = glm::vec3(0.0, 1.0, 0.0);
    origin = glm::vec3(0.0);
    MM = glm::mat4(1.0);
    texture = nullptr;
}

Entity::~Entity()
{
    if(texture) delete texture;
}

void Entity::setMMLocation(GLuint MMlocation)
{
    this->MMlocation = MMlocation;
}

void Entity::draw() const
{
    glBindVertexArray(VAO);
    glUniformMatrix4fv(MMlocation, 1, GL_FALSE, &MM[0][0]);
    glUniform1i(SUL2D_textured, (texture ? GL_TRUE : GL_FALSE));
    if(texture) texture->bind();
    specificDraw();
    glBindVertexArray(0);
}