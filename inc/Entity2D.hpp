
#ifndef ENTITY2D_HPP
#define ENTITY2D_HPP

#include "Entity.hpp"

class Entity2D : public Entity
{
public:

    ~Entity2D();

    glm::vec2 getPosition() const;
    void setPosition(const glm::vec2& position);
    void translate(const glm::vec2& translation);

    glm::vec2 getSize() const;
    void setSize(const glm::vec2& size);
    void scale(const glm::vec2& scalation);

    float getAngle() const;
    void setAngle(float angle);
    void rotate(float rotation);

    glm::vec2 getOrigin() const;
    void setOrigin(const glm::vec2& origin);

protected:

    Entity2D();

private:

};

#endif