
#include "RenderFrame.hpp"

#include "Program.hpp"

#include "GLM/gtc/matrix_transform.hpp"

const RenderFrame* RenderFrame::activeRenderFrame = nullptr;

RenderFrame::RenderFrame(const glm::ivec2& position, const glm::uvec2& size, const glm::vec4& clearColor)
{
    this->position = position;
    this->size = size;
    this->clearColor = clearColor;

    surfaceOrtho = glm::ortho(float(position.x), float(position.x+size.x), float(position.y+size.y), float(position.y));
}

RenderFrame::~RenderFrame() {}

glm::ivec2 RenderFrame::getPosition() const
{
    return position;
}

glm::uvec2 RenderFrame::getSize() const
{
    return size;
}

void RenderFrame::clean() const
{
    //Clear frame zone
    glScissor(position.x, position.y, size.x, size.y);
    glEnable(GL_SCISSOR_TEST);
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //stencil?
    glDisable(GL_SCISSOR_TEST);
}

void RenderFrame::draw(Entity3D& d)
{
    if(activeRenderFrame != this)
    {
        glViewport(position.x, position.y, size.x, size.y);
        activeRenderFrame = this;
    }
    d.draw();
}

void RenderFrame::drawOnSurface(Entity2D& d) //Change?
{
    if(activeRenderFrame != this)
    {
        glViewport(position.x, position.y, size.x, size.y);
        activeRenderFrame = this;
    }
    Program::getActiveProgram()->setUniformValue(SUL2D_WM, surfaceOrtho);
    glDisable(GL_DEPTH_TEST);
    d.draw();
    glEnable(GL_DEPTH_TEST);
}

void RenderFrame::sampleTexture(Texture* texture)
{
    texture->bind();
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, position.x, position.y, std::min(texture->getW(), int(size.x-position.x)), std::min(texture->getH(), int(size.y-position.y)));
}

const RenderFrame* RenderFrame::getActiveRenderFrame()
{
    return activeRenderFrame;
}