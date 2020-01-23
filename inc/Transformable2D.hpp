
#ifndef TRANSFORMABLE2D_HPP
#define TRANSFORMABLE2D_HPP

#include "GLM/glm.hpp"

#include "Transformable.hpp"

class Transformable2D : public Transformable
{
public:

    ~Transformable2D();

    glm::vec2 getCenter() const;
    glm::vec2 getSize() const;

    void setOrigin(const glm::vec2& origin);

    void setPosition(const glm::vec2& position);
    void applyTranslate(const glm::vec2& translate);

    void setScale(const glm::vec2& scale);
    void applyScale(const glm::vec2& scale);

protected:

    Transformable2D();

private:

    glm::vec2 origin;
};

#endif