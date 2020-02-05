
#include "Rectangle.hpp"

#include <vector>

#include "GLM/gtc/matrix_transform.hpp"

#include "Program.hpp"

unsigned int Rectangle::snumInstances = 0;
GLuint Rectangle::sVAO = 0;
GLuint Rectangle::siVBO = 0; 
GLuint Rectangle::svVBO = 0; 
GLuint Rectangle::stVBO = 0; 

Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size, const Texture* texture, const glm::vec4& color)
{
    this->texture = texture;
    this->position = glm::vec3(position, 0.0);
    this->size = glm::vec3(size, 1.0);
    MMOutOfDate = true;

    bb.first = glm::vec3(0.0, 0.0, 0.0);
    bb.second = glm::vec3(1.0, 1.0, 1.0);

    this->color = color;

    if(snumInstances == 0)
    {
        glGenVertexArrays(1, &sVAO);
        glBindVertexArray(sVAO);

        std::vector<float> vertices = { 0.0,    0.0,    0.0,
                                        1.0,    0.0,	0.0,
                                        0.0,    1.0,    0.0,
                                        1.0,    1.0,    0.0 };
        
        std::vector<float> texCoords = {0.0,    0.0,
                                        1.0,    0.0,
                                        0.0,    1.0,
                                        1.0,    1.0 };

        std::vector<unsigned int> indices = { 0,  2,  1,
                                              1,  2,  3 };

        glGenBuffers(1, &siVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, siVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &svVBO);
		glBindBuffer(GL_ARRAY_BUFFER, svVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL2D_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL2D_vertex);

        glGenBuffers(1, &stVBO);
		glBindBuffer(GL_ARRAY_BUFFER, stVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL2D_texCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL2D_texCoord);
        
        glBindVertexArray(0);
    }
    snumInstances++;

    VAO = sVAO;
    blending = true;
}

Rectangle::~Rectangle()
{
    snumInstances--;
    if(snumInstances == 0)
    {
        glDeleteBuffers(1, &siVBO);
        glDeleteBuffers(1, &svVBO);
        glDeleteBuffers(1, &stVBO);
        glDeleteVertexArrays(1, &sVAO);
    }
}

void Rectangle::specificDraw() const
{
    Program::getActiveProgram()->setUniformValue(SUL2D_color, color);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
}