
#ifndef RENDERFRAME_HPP
#define RENDERFRAME_HPP

#include "Camera.hpp"
#include "Drawable.hpp"
#include "RenderProcedure.hpp"

class Drawable;

class RenderFrame
{
public:

    RenderFrame(const glm::ivec2& position, const glm::uvec2& size, const glm::vec4& clearColor = glm::vec4(0.0, 0.0, 0.0, 1.0));
    ~RenderFrame();

    void startDrawing() const;
    void draw(const Drawable& d) const;
    void drawOnSurface(const Drawable& d) const;
    void render(const RenderProcedure& r) const;
    void endDrawing() const;

    Camera* getCamera();

private:

    glm::ivec2 position;
    glm::uvec2 size;

    glm::vec4 clearColor;

    Camera* camera;
};

#endif