
#include "RenderFrame.hpp"

RenderFrame::RenderFrame(glm::uvec2 position, glm::uvec2 size, glm::vec4 clearColor)
{
    this->position = position;
    this->size = size;
    this->clearColor = clearColor;

    camera = Camera::getDefaultCamera();
}

RenderFrame::~RenderFrame() {}

void RenderFrame::startDrawing() const
{
    //Clear frame zone
    glEnable(GL_SCISSOR_TEST);
    glScissor(position.x, position.y, size.x, size.y);
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //stencil?
    glDisable(GL_SCISSOR_TEST);

    glViewport(position.x, position.y, size.x, size.y);

    glUniformMatrix4fv(SUL::VM, 1, GL_FALSE, camera->getVM());
    glUniformMatrix4fv(SUL::PM, 1, GL_FALSE, camera->getPM());
}

void RenderFrame::draw(const Drawable& d) const
{
    d.draw();
}

void RenderFrame::drawOnSurface(const Drawable& d) const //Change?
{
    glm::mat4 ident(1.0);
    glm::mat4 ortho = glm::ortho(position.x, position.x+size.x, position.y+size.y, position.y);

    glUniformMatrix4fv(SUL::VM, 1, GL_FALSE, &ident[0][0]);
    glUniformMatrix4fv(SUL::PM, 1, GL_FALSE, &ortho[0][0]);

    glDisable(GL_DEPTH_TEST);

    d.draw();

    glEnable(GL_DEPTH_TEST);

    glUniformMatrix4fv(SUL::VM, 1, GL_FALSE, camera->getVM());
    glUniformMatrix4fv(SUL::PM, 1, GL_FALSE, camera->getPM());
}

void RenderFrame::render(const RenderProcedure& r) const
{
    r.render();
}

void RenderFrame::endDrawing() const
{
    
}

Camera* RenderFrame::getCamera()
{
    return camera;
}
