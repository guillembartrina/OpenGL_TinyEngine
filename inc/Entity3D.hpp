
#ifndef ENTITY3D_HPP
#define ENTITY3D_HPP

#include "Entity.hpp"

class Entity3D : public Entity
{
public:

    ~Entity3D();

    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3& position);
    void translate(const glm::vec3& translation);

    glm::vec3 getSize() const;
    void setSize(const glm::vec3& size);
    void scale(const glm::vec3& scalation);

    float getAngleX() const;
    float getAngleY() const;
    float getAngleZ() const;
    void setAngleX(float angle);
    void setAngleY(float angle);
    void setAngleZ(float angle);
    void rotateX(float rotation);
    void rotateY(float rotation);
    void rotateZ(float rotation);

    glm::vec3 getOrigin() const;
    void setOrigin(const glm::vec3& origin);
    
protected:

    Entity3D();

private:

};

#endif