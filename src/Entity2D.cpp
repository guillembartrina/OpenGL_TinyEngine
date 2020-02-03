
#include "Entity2D.hpp"

#include "GLM/gtc/matrix_transform.hpp"

Entity2D::Entity2D() {}

Entity2D::~Entity2D() {}

glm::vec2 Entity2D::getPosition() const
{
    return position;
}

void Entity2D::setPosition(const glm::vec2& position)
{
    this->position = glm::vec3(position, 0.0);
    MMOutOfDate = true;
}

void Entity2D::translate(const glm::vec2& translation)
{
    position += glm::vec3(translation, 0.0);
    MMOutOfDate = true;
}

glm::vec2 Entity2D::getSize() const
{
    return size;
}

void Entity2D::setSize(const glm::vec2& size)
{
    this->size = glm::vec3(size, 1.0);
    MMOutOfDate = true;
}

void Entity2D::scale(const glm::vec2& scalation)
{
    size *= glm::vec3(scalation, 1.0);
    MMOutOfDate = true;
}

float Entity2D::getAngle() const
{
    return rotZ;
}

void Entity2D::setAngle(float angle)
{
    rotZ = angle;
    MMOutOfDate = true;
}

void Entity2D::rotate(float rotation)
{
    rotZ += rotation;
    rotZ = glm::mod(rotZ, float(2.f*PI));
    MMOutOfDate = true;
}

glm::vec2 Entity2D::getOrigin() const
{
    return origin;
}

void Entity2D::setOrigin(const glm::vec2& origin)
{
    this->origin = glm::vec3(origin, 0.0);
    MMOutOfDate = true;
}