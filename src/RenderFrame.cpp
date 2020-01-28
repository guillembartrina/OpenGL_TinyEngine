
#include "RenderFrame.hpp"

RenderFrame::RenderFrame(const glm::ivec2& position, const glm::uvec2& size, const glm::vec4& clearColor)
{
    this->position = position;
    this->size = size;
    this->clearColor = clearColor;

    camera = new Camera();

    surfaceOrtho = glm::ortho(float(position.x), float(position.x+size.x), float(position.y+size.y), float(position.y));

    std::string drawVSsrc = 
    "#version 450\n"\
    "layout(location = 0)in vec3 vertex;"\
    "layout(location = 1)in vec3 normal;"\
    "layout(location = 2)in vec2 texCoord;"\
    "layout(location = 10)in vec3 ka;"\
    "layout(location = 11)in vec3 kd;"\
    "layout(location = 12)in vec3 ks;"\
    "layout(location = 13)in float ns;"\
    "out vec3 vvertex;"\
    "out vec3 vnormal;"\
    "out vec2 vtexCoord;"\
    "out vec3 vka;"\
    "out vec3 vkd;"\
    "out vec3 vks;"\
    "out float vns;"\
    "layout(location = 0)uniform mat4 MM;"\
    "layout(location = 1)uniform mat4 VM;"\
    "layout(location = 2)uniform mat4 PM;"\
    "void main()"\
    "{"\
    "vvertex = (VM * MM * vec4(vertex, 1.0)).xyz;"\
    "mat3 NM = inverse(transpose(mat3(VM * MM)));"\
    "vnormal = normalize(NM * normal);"\
    "vtexCoord = texCoord;"\
    "vka = ka;"\
    "vkd = kd;"\
    "vks = ks;"\
    "vns = ns;"\
    "gl_Position = PM * VM * MM * vec4(vertex, 1.0);"\
    "}";
    drawVS = new Shader(ShaderType::Vertex);
    drawVS->load_fromString(drawVSsrc);
    drawVS->compile();
    std::string drawFSsrc = 
    "#version 450\n"\
    "#define MAX_LIGHTS 64\n"\
    "in vec3 vvertex;"\
    "in vec3 vnormal;"\
    "in vec2 vtexCoord;"\
    "in vec3 vka;"\
    "in vec3 vkd;"\
    "in vec3 vks;"\
    "in float vns;"\
    "out vec4 fragColor;"\
    "layout(location = 1)uniform mat4 VM;"\
    "layout(location = 10)uniform bool textured;"\
    "layout(location = 11)uniform bool illumination;"\
    "layout(location = 20)uniform int numLights;"\
    "layout(location = 21)uniform vec3 lights[MAX_LIGHTS];"\
    "layout(binding = 0)uniform sampler2D tex;"\
    "vec3 Ambient()"\
    "{"\
    "return vec3(0.2, 0.2, 0.2);"\
    "}"\
    "vec3 Diffuse(vec3 light)"\
    "{"\
    "vec3 col = vec3(0.0, 0.0, 0.0);"\
    "vec3 L = normalize(light - vvertex);"\
    "float alpha = dot(vnormal, L);"\
    "if(alpha > 0)"\
    "{"\
    "col = vkd * alpha;"\
    "}"\
    "return (col);"\
    "}"\
    "vec3 Specular(vec3 light)"\
    "{"\
    "vec3 col = vec3(0.0, 0.0, 0.0);"\
    "vec3 L = normalize(light - vvertex);"\
    "float alpha = dot(vnormal, L);"\
    "if(alpha > 0)"\
    "{"\
    "vec3 R = reflect(-L, vnormal);"\
    "vec3 V = normalize(-light);"\
    "float beta = dot(R, V);"\
    "if(beta > 0 && vns > 0.0)"\
    "{"\
    "float shine = pow(max(0.0, beta), vns);"\
    "col = vks * shine;"\
    "}"\
    "}"\
    "return (col);"\
    "}"\
    "void main()"\
    "{"\
    "vec3 color = Ambient();"\
    "for(int i = 0; i < numLights; i++)"\
    "{"\
    "vec3 light = (VM * vec4(lights[i], 1.0)).xyz;"\
    "color += (Diffuse(light) + Specular(light));"\
    "}"\
    "fragColor = vec4(color, 1.0);"\
    "}";
    drawFS = new Shader(ShaderType::Fragment);
    drawFS->load_fromString(drawFSsrc);
    drawFS->compile();
    drawProgram = new Program();
    drawProgram->attachShader(*drawVS);
    drawProgram->attachShader(*drawFS);
    drawProgram->link();

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
    drawOnSurfaceVS->compile();
    std::string drawOnSurfaceFSsrc = 
    "#version 450\n"\
    "in vec2 vTexCoord;"\
    "layout(location = 10)uniform bool textured;"\
    "layout(location = 20)uniform vec4 color;"\
    "layout(binding = 0)uniform sampler2D tex;"\
    "void main()"\
    "{"\
    "if(textured) gl_FragColor = texture(tex, vTexCoord) * color;"\
    "else gl_FragColor = color;"\
    "}";
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

    glEnable(GL_DEPTH_TEST);
}

void RenderFrame::draw(const Drawable& d) const
{
    drawProgram->use();
    glUniform1i(SUL3D_numLights, lights.size());
    glUniform3fv(SUL3D_lights, lights.size(), &lights[0][0]); //max 64!
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

std::vector<glm::vec3>& RenderFrame::getLights()
{
    return lights;
}
