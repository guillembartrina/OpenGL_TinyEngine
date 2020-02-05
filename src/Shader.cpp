
#include "Shader.hpp"

#include <iostream>

#include "IO.hpp"

const std::string Shader::defaultShaders[ShaderType_NUM] = 
{
    //default VS
    "#version 450\n"\
    "layout(location = 0)in vec3 vertex;"\
    "layout(location = 0)uniform mat4 MM;"\
    "layout(location = 1)uniform mat4 VM;"\
    "layout(location = 2)uniform mat4 PM;"\
    "void main()"\
    "{"\
    "gl_Position = PM * VM * MM * vec4(vertex, 1.0);"\
    "}",
    //default GS
    "#version 450\n"\
    "layout(triangles) in;"\
    "layout(triangle_strip, max_vertices = 3) out;"\
    "void main()"\
    "{"\
    "for(int i = 0; i < 3; i++)"\
    "{"\
    "gl_Position = gl_in[i].gl_Position;"\
    "EmitVertex();"\
    "}"\
    "EndPrimitive();"\
    "}",
    //default FS
    "#version 450\n"\
    "out vec4 fragColor;"\
    "void main()"\
    "{"\
    "fragColor = vec4(1.0, 0.0, 1.0, 1.0);"\
    "}"
};

Shader::Shader(ShaderType type)
{
    GLenum t;
    switch(type)
    {
        case ShaderType_Vertex:
            t = GL_VERTEX_SHADER;
            break;
        case ShaderType_Geomerty:
            t = GL_GEOMETRY_SHADER;
            break;
        case ShaderType_Fragment:
            t = GL_FRAGMENT_SHADER;
            break;
    }
    this->type = type;
    id = glCreateShader(t);
    loaded = false;
    compiled = false;
}

Shader::~Shader()
{
	glDeleteShader(id);
}

void Shader::load_default()
{
    const GLchar* src = defaultShaders[type].c_str();
    glShaderSource(id, 1, &src, 0);
    loaded = true;
    compiled = false;
}

void Shader::load_fromString(const std::string& source)
{
    const GLchar* src = source.c_str();
    glShaderSource(id, 1, &src, 0);
    loaded = true;
    compiled = false;
}

bool Shader::load_fromFile(const std::string& path)
{
    std::string source;
    if(not IO::readFile(path, source)) return false;
    const GLchar* src = source.c_str();
    glShaderSource(id, 1, &src, 0);
    loaded = true;
    compiled = false;
    return true;
}

bool Shader::compile()
{
    if(loaded)
    {
        glCompileShader(id);
        GLint compiledFlag;
        glGetShaderiv(id, GL_COMPILE_STATUS, &compiledFlag);
        if(compiledFlag == GL_FALSE)
        {
            GLint lenght;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
            char* log = (char*)malloc(lenght);
            glGetShaderInfoLog(id, lenght, &lenght, log);
            std::cerr << "Shader: compiling error" << std::endl << log << std::endl;
            free((void*)log);
            return false;
        }
        compiled = true;
        return true;
    }
    else
    {
        std::cerr << "Shader: error compiling, shader not loaded" << std::endl;
    }
    return false;
}

ShaderType Shader::getType() const
{
    return type;
}

GLuint Shader::getId() const
{
    return id;
}

bool Shader::isLoaded() const
{
    return loaded;
}

bool Shader::isCompiled() const
{
    return compiled;
}