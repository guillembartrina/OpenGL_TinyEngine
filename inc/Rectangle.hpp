
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Drawable.hpp"
#include "Transformable2D.hpp"

class Rectangle : public Drawable, public Transformable2D
{
public:

    Rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0, 1.0, 1.0, 1.0));
    ~Rectangle();

    void draw() const;

private:

    glm::vec4 color;

    static bool loaded;
    static GLuint VAO;
    static void bindRectangle();
};

#endif