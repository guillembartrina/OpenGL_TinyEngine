
#ifndef ENTITY2D_HPP
#define ENTITY2D_HPP

#include "Entity.hpp"

class Entity2D : public Entity
{
public:

    ~Entity2D();

    glm::vec2 getCenter() const;
    glm::vec2 getSize() const;

    void setOrigin(const glm::vec2& origin);

    void setPosition(const glm::vec2& position);
    void applyTranslate(const glm::vec2& translate);

    void setSize(const glm::vec2& scale);
    void applyScale(const glm::vec2& scale);

    void rotate(float angle);

protected:

    Entity2D();

private:

};

#endif