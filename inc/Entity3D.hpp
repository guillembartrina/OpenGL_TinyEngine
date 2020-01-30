
#ifndef ENTITY3D_HPP
#define ENTITY3D_HPP

#include "Entity.hpp"

class Entity3D : public Entity
{
public:

    ~Entity3D();

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

    Entity3D();

private:

};

#endif