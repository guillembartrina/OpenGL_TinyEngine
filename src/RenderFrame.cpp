
#include "RenderFrame.hpp"

RenderFrame::RenderFrame(const glm::ivec2& position, const glm::uvec2& size, const glm::vec4& clearColor)
{
    this->position = position;
    this->size = size;
    this->clearColor = clearColor;

    camera = new Camera();

    surfaceOrtho = glm::ortho(float(position.x), float(position.x+size.x), float(position.y+size.y), float(position.y));

    /*
    std::string drawVSsrc = "";
    drawVS = new Shader(ShaderType::Vertex);
    drawVS->load_fromString(drawVSsrc);

    std::string drawFSsrc = "";
    drawFS = new Shader(ShaderType::Fragment);
    drawFS->load_fromString(drawFSsrc);
    drawProgram = new Program();
    drawProgram->attachShader(*drawVS);
    drawProgram->attachShader(*drawFS);
    drawProgram->link();
    */

    std::string drawOnSurfaceVSsrc =
    "#version 450\n"
    "layout(location = 0)in vec3 vertex;"\
    "layout(location = 1)in vec2 texCoord;"\
    "out vec2 vTexCoord;"\
    "layout(location = 0)uniform mat4 MM;"\
    "layout(location = 1)uniform mat4 SM;"\
    "void main()"\
    "{"\
    "vTexCoord = texCoord;"\
    "gl_Position = SM * MM * vec4(vertex, 1.0);"\
    "}";
    drawOnSurfaceVS = new Shader(ShaderType::Vertex);
    drawOnSurfaceVS->load_fromString(drawOnSurfaceVSsrc);
    std::string drawOnSurfaceFSsrc = 
    "#version 450\n"\
    "in vec2 vTexCoord;"\
    "layout(location = 10)uniform vec4 color;"\
    "layout(location = 20)uniform bool textured;"\
    "layout(binding = 0)uniform sampler2D tex;"\
    "void main()"\
    "{"\
    "if(textured) gl_FragColor = texture(tex, vTexCoord) * color;"\
    "else gl_FragColor = color;"\
    "}";
    drawOnSurfaceVS->compile();
    drawOnSurfaceFS = new Shader(ShaderType::Fragment);
    drawOnSurfaceFS->load_fromString(drawOnSurfaceFSsrc);
    drawOnSurfaceFS->compile();
    drawOnSurfaceProgram = new Program();
    drawOnSurfaceProgram->attachShader(*drawOnSurfaceVS);
    drawOnSurfaceProgram->attachShader(*drawOnSurfaceFS);
    drawOnSurfaceProgram->link();
}

RenderFrame::~RenderFrame()
{
    delete camera;
}

void RenderFrame::startDrawing() const
{
    //Clear frame zone
    glEnable(GL_SCISSOR_TEST);
    glScissor(position.x, position.y, size.x, size.y);
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //stencil?

    glViewport(position.x, position.y, size.x, size.y);
}

void RenderFrame::draw(const Drawable& d) const
{
    drawProgram->use();
    glUniformMatrix4fv(SUL3D_VM, 1, GL_FALSE, camera->getVM());
    glUniformMatrix4fv(SUL3D_PM, 1, GL_FALSE, camera->getPM());
    d.draw();
}

void RenderFrame::drawOnSurface(const Drawable& d) const //Change?
{
    drawOnSurfaceProgram->use();
    glUniformMatrix4fv(SUL2D_WM, 1, GL_FALSE, &surfaceOrtho[0][0]);
    glDisable(GL_DEPTH_TEST);
    d.draw();
    glEnable(GL_DEPTH_TEST);
}

void RenderFrame::render(const RenderProcedure& r) const
{
    r.render(*this);
}

void RenderFrame::endDrawing() const
{
    glDisable(GL_SCISSOR_TEST);
}

Camera* RenderFrame::getCamera()
{
    return camera;
}
