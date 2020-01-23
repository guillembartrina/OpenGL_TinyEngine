
#include "Rectangle.hpp"

#include <vector>

bool Rectangle::loaded = false;  
GLuint Rectangle::VAO = 0;  

Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    center = glm::vec3(0.0, 0.0, 0.0);
    bb.first = glm::vec3(-0.5, -0.5, 0.0);
    bb.second = glm::vec3(0.5, 0.5, 0.0);

    MM = glm::translate(identity, center) * glm::scale(identity, glm::vec3(size, 0.0));

    this->color = color;
}

Rectangle::~Rectangle() {}

void Rectangle::draw() const
{
    bindRectangle();
    Transformable2D::bind();
    glUniform4fv(SUL::color, 1, &color[0]);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Rectangle::bindRectangle()
{
    if(not loaded)
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        std::vector<float> vertices = { -0.5,   -0.5,   0.0,
                                        0.5,    -0.5,	0.0,
                                        -0.5,   0.5,    0.0,
                                        0.5,    0.5,    0.0 };

        std::vector<unsigned int> indices = { 1,  2,  0,
                                              1,  3,  2 };

        GLuint tmpVBO;

        glGenBuffers(1, &tmpVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL::vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL::vertex);
        
        glBindVertexArray(0);

        loaded = true;
    }

    glBindVertexArray(VAO);
}