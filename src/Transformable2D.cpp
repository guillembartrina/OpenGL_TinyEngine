
#include "Transformable2D.hpp"

#include "GLM/gtc/matrix_transform.hpp"

Transformable2D::Transformable2D()
{
    MM = glm::mat4(1.0);
    origin = glm::vec2(0.0);
}

Transformable2D::~Transformable2D() {}

glm::vec2 Transformable2D::getCenter() const
{
    return glm::vec2(MM * glm::vec4(center + glm::vec3(origin, 0.0), 1.0));
}

glm::vec2 Transformable2D::getSize() const
{
    glm::vec3 min = glm::vec3(MM * glm::vec4(bb.first, 1.0));
    glm::vec3 max = glm::vec3(MM * glm::vec4(bb.second, 1.0));

    return max - min;
}

void Transformable2D::setOrigin(const glm::vec2& origin)
{
    this->origin = origin;
}

void Transformable2D::setPosition(const glm::vec2& position)
{
    glm::vec2 pos = glm::vec2(MM * glm::vec4(center + glm::vec3(origin, 0.0), 1.0));
    MM = glm::translate(identity, -glm::vec3(pos, 0.0)) * MM;
    MM = glm::translate(identity, glm::vec3(position, 0.0)) * MM;
}

void Transformable2D::applyTranslate(const glm::vec2& translate)
{
    MM = glm::translate(identity, glm::vec3(translate, 0.0)) * MM;
}

void Transformable2D::setSize(const glm::vec2& scale)
{
    glm::vec2 size = getSize();
    glm::vec2 pos = glm::vec2(MM * glm::vec4(center + glm::vec3(origin, 0.0), 1.0));
    MM = glm::translate(identity, -glm::vec3(pos, 0.0)) * MM;
    MM = glm::scale(identity, glm::vec3(scale.x / size.x, scale.y / size.y, 0.0)) * MM;
    MM = glm::translate(identity, glm::vec3(pos, 0.0)) * MM;
}

void Transformable2D::applyScale(const glm::vec2& scale)
{
    MM = glm::scale(identity, glm::vec3(scale, 1.0)) * MM;
}

void Transformable2D::rotate(float angle)
{
    glm::vec2 pos = glm::vec2(MM * glm::vec4(center + glm::vec3(origin, 0.0), 1.0));
    MM = glm::translate(identity, -glm::vec3(pos, 0.0)) * MM;
    MM = glm::rotate(identity, angle, glm::vec3(0.0, 0.0, 1.0)) * MM;
    MM = glm::translate(identity, glm::vec3(pos, 0.0)) * MM;
}