
#include "Entity3D.hpp"

#define PI 3.14159265358979323846

#include "GLM/gtc/matrix_transform.hpp"

Entity3D::Entity3D() {}

Entity3D::~Entity3D() {}

glm::vec3 Entity3D::getPosition() const
{
    return position;
}

void Entity3D::setPosition(const glm::vec3& position)
{
    this->position = position;
    MMOutOfDate = true;
}

void Entity3D::translate(const glm::vec3& translation)
{
    position += translation;
    MMOutOfDate = true;
}

glm::vec3 Entity3D::getSize() const
{
    return size;
}

void Entity3D::setSize(const glm::vec3& size)
{
    this->size = size;
    MMOutOfDate = true;
}

void Entity3D::scale(const glm::vec3& scalation)
{
    size *= scalation;
    MMOutOfDate = true;
}

float Entity3D::getAngleX() const
{
    return rotX;
}

float Entity3D::getAngleY() const
{
    return rotY;
}

float Entity3D::getAngleZ() const
{
    return rotZ;
}

void Entity3D::setAngleX(float angle)
{
    rotX = angle;
    MMOutOfDate = true;
}

void Entity3D::setAngleY(float angle)
{
    rotY = angle;
    MMOutOfDate = true;
}

void Entity3D::setAngleZ(float angle)
{
    rotZ = angle;
    MMOutOfDate = true;
}

void Entity3D::rotateX(float rotation)
{
    rotX += rotation;
    rotX = glm::mod(rotX, float(2.f*PI));
    MMOutOfDate = true;
}

void Entity3D::rotateY(float rotation)
{
    rotY += rotation;
    rotY = glm::mod(rotY, float(2.f*PI));
    MMOutOfDate = true;
}

void Entity3D::rotateZ(float rotation)
{
    rotZ += rotation;
    rotZ = glm::mod(rotZ, float(2.f*PI));
    MMOutOfDate = true;
}

glm::vec3 Entity3D::getOrigin() const
{
    return origin;
}

void Entity3D::setOrigin(const glm::vec3& origin)
{
    this->origin = origin;
    MMOutOfDate = true;
}