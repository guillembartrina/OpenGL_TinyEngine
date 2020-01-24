
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Drawable.hpp"
#include "Transformable2D.hpp"
#include "Texture.hpp"

class Rectangle : public Drawable, public Transformable2D
{
public:

    Rectangle(const glm::vec2& position, const glm::vec2& size, const Texture* texture, const glm::vec4& color = glm::vec4(1.0, 1.0, 1.0, 1.0));
    ~Rectangle();

    void draw() const;

private:

    glm::vec4 color;

    const Texture* texture;

    static unsigned int numInstances;
    static GLuint VAO;
    static GLuint iVBO, vVBO, tVBO;
};

#endif