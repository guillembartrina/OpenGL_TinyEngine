
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Entity2D.hpp"

class Rectangle : public Entity2D
{
public:

    Rectangle(const glm::vec2& position, const glm::vec2& size, const Texture* texture, const glm::vec4& color = glm::vec4(1.0, 1.0, 1.0, 1.0));
    ~Rectangle();

private:

    void specificDraw() const;

    glm::vec4 color;

    static unsigned int snumInstances;
    static GLuint sVAO;
    static GLuint siVBO, svVBO, stVBO;
};

#endif