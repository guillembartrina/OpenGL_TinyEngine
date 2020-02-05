
#ifndef RENDERFRAME_HPP
#define RENDERFRAME_HPP

#include "Program.hpp"
#include "Camera.hpp"
#include "Entity2D.hpp"
#include "Entity3D.hpp"
#include "RenderProcedure.hpp"

class RenderProcedure;

class RenderFrame
{
public:

    RenderFrame(const glm::ivec2& position, const glm::uvec2& size, const glm::vec4& clearColor = glm::vec4(0.0, 0.0, 0.0, 1.0));
    ~RenderFrame();

    glm::uvec2 getSize() const;
    
    void clean() const;
    void draw(Entity3D& d);
    void drawOnSurface(Entity2D& d);
    void render(RenderProcedure& r);

    void sampleTexture(Texture* texture);

    static const RenderFrame* getActiveRenderFrame();

private:

    glm::ivec2 position;
    glm::uvec2 size;

    glm::vec4 clearColor;

    glm::mat4 surfaceOrtho;

    static const RenderFrame* activeRenderFrame;
};

#endif