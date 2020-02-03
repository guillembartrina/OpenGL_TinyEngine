
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

    //void setDrawProgram(Program* prog);
    //void setDrawOnSurfaceProgram(Program* prog):

    void startDrawing() const;
    void draw(Entity3D& d);
    void drawOnSurface(Entity2D& d);
    void render(const RenderProcedure& r);
    void endDrawing() const;

    Camera* getCamera();
    std::vector<glm::vec3>& getLights();

    void sampleTexture(Texture* texture);

private:

    glm::ivec2 position;
    glm::uvec2 size;

    glm::vec4 clearColor;

    Camera* camera;

    std::vector<glm::vec3> lights;

    glm::mat4 surfaceOrtho;

    bool loadedDraw, loadedDrawOnSurface;

    Program* drawProgram;
    Program* drawOnSurfaceProgram;

    static unsigned int snumInstances;
    static Shader* sdrawVS;
    static Shader* sdrawFS;
    static Program* sdrawProgram;
    static Shader* sdrawOnSurfaceVS;
    static Shader* sdrawOnSurfaceFS;
    static Program* sdrawOnSurfaceProgram;
};

#endif