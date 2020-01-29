
#ifndef TRANSFORMABLE3D_HPP
#define TRANSFORMABLE3D_HPP

#include "GLM/glm.hpp"

#include "Transformable.hpp"

class Transformable3D : public Transformable
{
public:

    ~Transformable3D();

    glm::vec3 getCenter() const;
    glm::vec3 getSize() const;

    void setOrigin(const glm::vec3& origin);

    void setPosition(const glm::vec3& position);
    void applyTranslate(const glm::vec3& translate);

    void setSize(const glm::vec3& scale);
    void applyScale(const glm::vec3& scale);

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void applyRotation(float angle, const glm::vec3& axis);
    
    void applyTransform(const glm::mat4& transform);

protected:

    Transformable3D();

private:

    glm::vec3 origin;
};

#endif