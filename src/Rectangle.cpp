
#include "Rectangle.hpp"

#include <vector>
#include <iostream>

unsigned int Rectangle::numInstances = 0;
GLuint Rectangle::VAO = 0;
GLuint Rectangle::iVBO = 0; 
GLuint Rectangle::vVBO = 0; 
GLuint Rectangle::tVBO = 0; 

Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size, const Texture* texture, const glm::vec4& color)
{
    center = glm::vec3(0.0, 0.0, 0.0);
    bb.first = glm::vec3(-0.5, -0.5, 0.0);
    bb.second = glm::vec3(0.5, 0.5, 0.0);

    MM = glm::translate(identity, glm::vec3(position, 0.0)) * glm::scale(identity, glm::vec3(size, 0.0));

    this->color = color;
    this->texture = texture;

    if(numInstances == 0)
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        std::vector<float> vertices = { -0.5,   -0.5,   0.0,
                                        0.5,    -0.5,	0.0,
                                        -0.5,   0.5,    0.0,
                                        0.5,    0.5,    0.0 };
        
        std::vector<float> texCoords = {0.0,    0.0,
                                        1.0,    0.0,
                                        0.0,    1.0,
                                        1.0,    1.0 };

        std::vector<unsigned int> indices = { 1,  2,  0,
                                              1,  3,  2 };

        glGenBuffers(1, &iVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &vVBO);
		glBindBuffer(GL_ARRAY_BUFFER, vVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL2D_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL2D_vertex);

        glGenBuffers(1, &tVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL2D_texCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL2D_texCoord);
        
        glBindVertexArray(0);
    }
    numInstances++;
}

Rectangle::~Rectangle()
{
    numInstances--;
    if(numInstances == 0)
    {
        glDeleteBuffers(1, &iVBO);
        glDeleteBuffers(1, &vVBO);
        glDeleteBuffers(1, &tVBO);
        glDeleteVertexArrays(1, &VAO);
    }
}

void Rectangle::draw() const
{
    glBindVertexArray(VAO);
    Transformable2D::bind();
    glUniform4fv(SUL2D_color, 1, &color[0]);
    glUniform1i(SUL2D_textured, (texture ? GL_TRUE : GL_FALSE));
    if(texture) texture->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
    glBindVertexArray(0);
}