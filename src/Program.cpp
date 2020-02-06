
#include "Program.hpp"

#include <iostream>

const Program* Program::activeProgram = nullptr;

Shader* Program::drawVS = nullptr;
Shader* Program::drawFS = nullptr;
Program* Program::drawProgram = nullptr;
Shader* Program::drawOnSurfaceVS = nullptr;
Shader* Program::drawOnSurfaceFS = nullptr;
Program* Program::drawOnSurfaceProgram = nullptr;

Program::Program()
{
	id = glCreateProgram();
	for(unsigned int i = 0; i < ShaderType_NUM; i++)
	{
		shaderIds[i] = -1;
	}
	linked = false;
}

Program::~Program()
{
	for(unsigned int i = 0; i < ShaderType_NUM; i++)
	{
		if(shaderIds[i] != -1) glDetachShader(id, shaderIds[i]);
	}
	glDeleteProgram(id);
}

void Program::attachShader(const Shader& shader)
{
	if(shader.isCompiled())
	{
		ShaderType type = shader.getType();
		shaderIds[type] = shader.getId(); 
		glAttachShader(id, shaderIds[type]);
	}
	else
    {
        std::cerr << "Program: error attaching shader, shader not compiled" << std::endl;
    }
}

void Program::defineAttributesLocation(const std::vector<std::pair<std::string, GLuint>>& data)
{
	if(linked) std::cerr << "Program: defining attributes location while linked, program needs to be relinked" << std::endl;
	
	for(unsigned int i = 0; i < data.size(); i++)
	{
		glBindAttribLocation(id, data[i].second, data[i].first.c_str());
	}
}

bool Program::link()
{
	glLinkProgram(id);
	GLint linkedFlag;
	glGetProgramiv(id, GL_LINK_STATUS, &linkedFlag);
	if(linkedFlag == GL_FALSE)
	{
		GLint lenght;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* log = (char*)malloc(lenght);
		glGetProgramInfoLog(id, lenght, &lenght, log);
		std::cerr << "Program: linking error"<< std::endl << log << std::endl;
		free((void*)log);
		return false;
	}
	glValidateProgram(id);
	GLint validatedFlag;
	glGetProgramiv(id, GL_VALIDATE_STATUS, &validatedFlag);
	if(validatedFlag == GL_FALSE)
	{
		GLint lenght;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* log = (char*)malloc(lenght);
		glGetProgramInfoLog(id, lenght, &lenght, log);
		std::cerr << "Program: validating error"<< std::endl << log << std::endl;
		free((void*)log);
		return false;
	}
	linked = true;
	return true;
}

GLuint Program::getAttributeLocation(const std::string& name) const
{
	if(linked)
	{
		GLuint loc = glGetAttribLocation(id, name.c_str());
		if(loc == -1) std::cerr << "Program: attribute <" + name + "> not found" << std::endl;
		else return loc;
	}
	else
    {
        std::cerr << "Program: error getting attribute location, program not linked" << std::endl;
    }
	return -1;
}

GLuint Program::getUniformLocation(const std::string& name) const
{
	if(linked)
	{
		GLuint loc = glGetUniformLocation(id, name.c_str());
		if(loc == -1) std::cerr << "Program: uniform <" + name + "> not found" << std::endl;
		else return loc;
	}
	else
    {
        std::cerr << "Program: error getting uniform location, program not linked" << std::endl;
    }
	return -1;
}

GLuint Program::getId() const
{
	return id;
}

void Program::use() const
{
	if(linked)
	{
        if(activeProgram != this)
        {
            glUseProgram(id);
            activeProgram = this;
        }
	}
	else
    {
        std::cerr << "Program: error using, program not linked" << std::endl;
		activeProgram = nullptr;
    }
}

void Program::setUniformValue(GLuint location, int value) const
{
	if(linked)
	{
		if(activeProgram != this) use();
		glUniform1i(location, value);
	}
	else
    {
        std::cerr << "Program: error setting uniform int, program not linked" << std::endl;
    }
}

void Program::setUniformValue(GLuint location, float value) const
{
	if(linked)
	{
		if(activeProgram != this) use();
		glUniform1f(location, value);
	}
	else
    {
        std::cerr << "Program: error setting uniform float, program not linked" << std::endl;
    }
}

void Program::setUniformValue(GLuint location, const glm::vec2& value) const
{
	if(linked)
	{
		if(activeProgram != this) use();
		glUniform2fv(location, 1, &value[0]);
	}
	else
    {
        std::cerr << "Program: error setting uniform vec2, program not linked" << std::endl;
    }
}

void Program::setUniformValue(GLuint location, const glm::vec3& value) const
{
	if(linked)
	{
		if(activeProgram != this) use();
		glUniform3fv(location, 1, &value[0]);
	}
	else
    {
        std::cerr << "Program: error setting uniform vec3, program not linked" << std::endl;
    }
}

void Program::setUniformValue(GLuint location, const glm::vec4& value) const
{
	if(linked)
	{
		if(activeProgram != this) use();
		glUniform4fv(location, 1, &value[0]);
	}
	else
    {
        std::cerr << "Program: error setting uniform vec4, program not linked" << std::endl;
    }
}

void Program::setUniformValue(GLuint location, const glm::mat3& value) const
{
	if(linked)
	{
		if(activeProgram != this) use();
		glUniformMatrix3fv(location, 1, false, &value[0][0]);
	}
	else
    {
        std::cerr << "Program: error setting uniform mat3, program not linked" << std::endl;
    }
}

void Program::setUniformValue(GLuint location, const glm::mat4& value) const
{
	if(linked)
	{
		if(activeProgram != this) use();
		glUniformMatrix4fv(location, 1, false, &value[0][0]);
	}
	else
    {
        std::cerr << "Program: error setting uniform mat4, program not linked" << std::endl;
    }
}

void Program::setUniformValue(GLuint location, const std::vector<glm::vec3>& value) const
{
	if(linked)
	{
		if(activeProgram != this) use();
		glUniform3fv(location, value.size(), &value[0][0]);
	}
	else
    {
        std::cerr << "Program: error setting uniform vector<vec3>, program not linked" << std::endl;
    }
}

bool  Program::isLinked() const
{
	return linked;
}

bool Program::isAttached(ShaderType type) const
{
	return (shaderIds[type] != -1);
}

const Program* Program::getActiveProgram()
{
	return activeProgram;
}

const Program* Program::getDefaultDrawProgram()
{
    if(drawProgram == nullptr)
    {
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
        drawVS = new Shader(ShaderType_Vertex);
        drawVS->load_fromString(drawVSsrc);
        drawVS->compile();
        std::string drawFSsrc = 
        "#version 450\n"\
        "#define MAX_LIGHTS 32\n"\
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
        "layout(location = 20)uniform int numLights;"\
        "layout(location = 21)uniform vec3 lights[MAX_LIGHTS];"\
        "layout(binding = 0)uniform sampler2D tex;"\
        "vec3 Ambient()"\
        "{"\
        "return (vka);"\
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
        "vec3 V = normalize(-vvertex);"\
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
        "vec3 color;"\
        "color = Ambient();"\
        "for(int i = 0; i < numLights; i++)"\
        "{"\
        "vec3 light = (VM * vec4(lights[i], 1.0)).xyz;"\
        "color += (Diffuse(light) + Specular(light));"\
        "}"\
        "if(textured) fragColor = texture(tex, vtexCoord) * vec4(color, 1.0);"
        "else fragColor = vec4(color, 1.0);"\
        "}";
        drawFS = new Shader(ShaderType_Fragment);
        drawFS->load_fromString(drawFSsrc);
        drawFS->compile();
        drawProgram = new Program();
        drawProgram->attachShader(*drawVS);
        drawProgram->attachShader(*drawFS);
        drawProgram->link();

        //vks * shine
    }

	return drawProgram;
}

const Program* Program::getDefaultDrawOnSurfaceProgram()
{
    if(drawOnSurfaceProgram == nullptr)
    {
        std::string drawOnSurfaceVSsrc =
        "#version 450\n"
        "layout(location = 0)in vec3 vertex;"\
        "layout(location = 1)in vec2 texCoord;"\
        "out vec2 vtexCoord;"\
        "layout(location = 0)uniform mat4 MM;"\
        "layout(location = 1)uniform mat4 WM;"\
        "void main()"\
        "{"\
        "vtexCoord = texCoord;"\
        "gl_Position = WM * MM * vec4(vertex, 1.0);"\
        "}";
        drawOnSurfaceVS = new Shader(ShaderType_Vertex);
        drawOnSurfaceVS->load_fromString(drawOnSurfaceVSsrc);
        drawOnSurfaceVS->compile();
        std::string drawOnSurfaceFSsrc = 
        "#version 450\n"\
        "in vec2 vtexCoord;"\
        "out vec4 fragColor;"\
        "layout(location = 10)uniform bool textured;"\
        "layout(location = 20)uniform vec4 color;"\
        "layout(binding = 0)uniform sampler2D tex;"\
        "void main()"\
        "{"\
        "if(textured) fragColor = texture(tex, vtexCoord) * color;"\
        "else fragColor = color;"\
        "}";
        drawOnSurfaceFS = new Shader(ShaderType_Fragment);
        drawOnSurfaceFS->load_fromString(drawOnSurfaceFSsrc);
        drawOnSurfaceFS->compile();
        drawOnSurfaceProgram = new Program();
        drawOnSurfaceProgram->attachShader(*drawOnSurfaceVS);
        drawOnSurfaceProgram->attachShader(*drawOnSurfaceFS);
        drawOnSurfaceProgram->link();
    }

    return drawOnSurfaceProgram;
}