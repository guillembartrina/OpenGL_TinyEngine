
#include "Entity2D.hpp"

#include "GLM/gtc/matrix_transform.hpp"

Entity2D::Entity2D() {}

Entity2D::~Entity2D() {}

glm::vec2 Entity2D::getCenter() const
{
    return glm::vec2(MM * glm::vec4(center + origin, 1.0));
}

glm::vec2 Entity2D::getSize() const
{
    glm::vec3 min = glm::vec3(MM * glm::vec4(bb.first, 1.0));
    glm::vec3 max = glm::vec3(MM * glm::vec4(bb.second, 1.0));

    return (max - min);
}

void Entity2D::setOrigin(const glm::vec2& origin)
{
    this->origin = glm::vec3(origin, 0.0);
}

void Entity2D::setPosition(const glm::vec2& position)
{
    glm::vec2 pos = glm::vec2(MM * glm::vec4(center + origin, 1.0));
    MM = glm::translate(identity, -glm::vec3(pos, 0.0)) * MM;
    MM = glm::translate(identity, glm::vec3(position, 0.0)) * MM;
}

void Entity2D::applyTranslate(const glm::vec2& translate)
{
    MM = glm::translate(identity, glm::vec3(translate, 0.0)) * MM;
}

void Entity2D::setSize(const glm::vec2& scale)
{
    glm::vec2 size = getSize();
    glm::vec2 pos = glm::vec2(MM * glm::vec4(center + origin, 1.0));
    MM = glm::translate(identity, -glm::vec3(pos, 0.0)) * MM;
    MM = glm::scale(identity, glm::vec3(scale.x / size.x, scale.y / size.y, 0.0)) * MM;
    MM = glm::translate(identity, glm::vec3(pos, 0.0)) * MM;
}

void Entity2D::applyScale(const glm::vec2& scale)
{
    MM = glm::scale(identity, glm::vec3(scale, 1.0)) * MM;
}

void Entity2D::rotate(float angle)
{
    glm::vec2 pos = glm::vec2(MM * glm::vec4(center + origin, 1.0));
    MM = glm::translate(identity, -glm::vec3(pos, 0.0)) * MM;
    MM = glm::rotate(identity, angle, glm::vec3(0.0, 0.0, 1.0)) * MM;
    MM = glm::translate(identity, glm::vec3(pos, 0.0)) * MM;
}