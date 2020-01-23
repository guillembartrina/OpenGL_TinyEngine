
#include "Transformable3D.hpp"

#include "GLM/gtc/matrix_transform.hpp"

Transformable3D::Transformable3D()
{
    MM = glm::mat4(1.0);
    origin = glm::vec3(0.0);
}

Transformable3D::~Transformable3D() {}

glm::vec3 Transformable3D::getCenter() const
{
    return glm::vec3(MM * glm::vec4(center + origin, 1.0));
}

glm::vec3 Transformable3D::getSize() const
{
    glm::vec3 min = glm::vec3(MM * glm::vec4(bb.first, 1.0));
    glm::vec3 max = glm::vec3(MM * glm::vec4(bb.second, 1.0));

    return max - min;
}

void Transformable3D::setOrigin(const glm::vec3& origin)
{
    this->origin = origin;
}

void Transformable3D::setPosition(const glm::vec3& position)
{
    glm::vec3 pos = glm::vec3(MM * glm::vec4(center + origin, 1.0));
    MM = glm::translate(identity, -pos) * MM;
    MM = glm::translate(identity, position) * MM;
}

void Transformable3D::applyTranslate(const glm::vec3& translate)
{
    MM = glm::translate(identity, translate) * MM;
}

void Transformable3D::setScale(const glm::vec3& scale)
{
    glm::vec3 size = getSize();
    glm::vec3 pos = glm::vec3(MM * glm::vec4(center + origin, 1.0));
    MM = glm::translate(identity, -pos) * MM;
    MM = glm::scale(identity, glm::vec3(scale.x / size.x, scale.y / size.y, scale.z / size.z)) * MM;
    MM = glm::translate(identity, pos) * MM;
}

void Transformable3D::applyScale(const glm::vec3& scale)
{
    MM = glm::scale(identity, scale) * MM;
}

void Transformable3D::applyTransform(const glm::mat4& transform)
{
    MM = transform * MM;
}