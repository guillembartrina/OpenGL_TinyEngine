
#include "TestRP.hpp"

#include <iostream>

TestRP::TestRP(Texture* texture)
{
    plane = Model3D::plane();
    plane->translate(glm::vec3(-0.5));
    plane->scale(glm::vec3(2.0));

    std::string vsSrc =
    "#version 450\n"\
    "layout(location = 0)in vec3 vertex;"\
    "layout(location = 2)in vec2 texCoord;"\
    "layout(location = 0)uniform mat4 MM;"\
    "out vec2 vtexCoord;"\
    "void main()"\
    "{"\
    "vtexCoord = texCoord;"\
    "gl_Position = MM * vec4(vertex, 1.0);"\
    "}";
    vs = new Shader(ShaderType::Vertex);
    vs->load_fromString(vsSrc);
    vs->compile();

    std::string fsSrc =
    "#version 450\n"\
    "layout(binding = 0)uniform sampler2D tex;"\
    "in vec2 vtexCoord;"\
    "out vec4 fragColor;"\
    "void main()"\
    "{"\
    "fragColor = texture(tex, vtexCoord);"\
    "}";
    fs = new Shader(ShaderType::Fragment);
    fs->load_fromString(fsSrc);
    fs->compile();

    p = new Program();
    p->attachShader(*vs);
    p->attachShader(*fs);
    p->link();

    this->texture = texture;
}

TestRP::~TestRP()
{
    delete p;
    delete vs, fs;
    delete plane;
}

Texture* TestRP::getTexture()
{
    return texture;
}

void TestRP::init(const RenderFrame& rf) {}

void TestRP::render(const RenderFrame& rf) const
{
    p->use();
    texture->bind();
    plane->draw();
}