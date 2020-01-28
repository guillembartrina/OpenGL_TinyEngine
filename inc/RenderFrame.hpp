
#ifndef RENDERFRAME_HPP
#define RENDERFRAME_HPP

#include "Shader.hpp"
#include "Program.hpp"
#include "Camera.hpp"
#include "Drawable.hpp"
#include "RenderProcedure.hpp"

class Drawable;
class RenderProcedure;

class RenderFrame
{
public:

    RenderFrame(const glm::ivec2& position, const glm::uvec2& size, const glm::vec4& clearColor = glm::vec4(0.0, 0.0, 0.0, 1.0));
    ~RenderFrame();

    //void setDrawProgram(Program* prog);
    //void setDrawOnSurfaceProgram(Program* prog):

    void startDrawing() const;
    void draw(const Drawable& d) const;
    void drawOnSurface(const Drawable& d) const;
    void render(const RenderProcedure& r) const;
    void endDrawing() const;

    Camera* getCamera();
    std::vector<glm::vec3>& getLights();

private:

    glm::ivec2 position;
    glm::uvec2 size;

    glm::vec4 clearColor;

    Camera* camera;

    std::vector<glm::vec3> lights;

    glm::mat4 surfaceOrtho;

    Shader* drawVS, *drawFS;
    Program* drawProgram;
    Shader* drawOnSurfaceVS, *drawOnSurfaceFS;
    Program* drawOnSurfaceProgram;
};

#endif