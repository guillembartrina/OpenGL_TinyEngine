
#include "RenderFrame.hpp"

#include <iostream>

const RenderFrame* RenderFrame::activeRenderFrame = nullptr;

RenderFrame::RenderFrame(const glm::ivec2& position, const glm::uvec2& size, const glm::vec4& clearColor)
{
    this->position = position;
    this->size = size;
    this->clearColor = clearColor;

    surfaceOrtho = glm::ortho(float(position.x), float(position.x+size.x), float(position.y+size.y), float(position.y));
}

RenderFrame::~RenderFrame() {}

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
    glViewport(position.x, position.y, size.x, size.y);
    //loadedDraw = loadedDrawOnSurface = false; !!!s
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
    Program::getActiveProgram()->setUniformValue(SUL2D_WM, surfaceOrtho);
    glDisable(GL_DEPTH_TEST);
    d.draw();
    glEnable(GL_DEPTH_TEST);
}

void RenderFrame::render(RenderProcedure& r)
{
    r.render(*this);
}

void RenderFrame::sampleTexture(Texture* texture)
{
    texture->bind();
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, position.x, position.y, std::min(texture->getW(), int(size.x)), std::min(texture->getH(), int(size.y)));
}

const RenderFrame* RenderFrame::getActiveRenderFrame()
{
    return activeRenderFrame;
}

/*
if(not loadedDraw)
    {
        drawProgram->use();
        glUniform1i(SUL3D_numLights, lights.size());
        glUniform3fv(SUL3D_lights, lights.size(), &lights[0][0]); //max 64!
        glUniformMatrix4fv(SUL3D_VM, 1, GL_FALSE, camera->getVM());
        glUniformMatrix4fv(SUL3D_PM, 1, GL_FALSE, camera->getPM());
        loadedDraw = true;
        loadedDrawOnSurface = false;
    }
    */