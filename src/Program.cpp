
#include "Program.hpp"

#include <iostream>

Program::Program()
{
	id = glCreateProgram();
	for(unsigned int i = 0; i < ShaderType::ShaderType_NUM; i++)
	{
		shaderIds[i] = -1;
	}
	linked = false;
}

Program::~Program()
{
	for(unsigned int i = 0; i < ShaderType::ShaderType_NUM; i++)
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

GLuint Program::getAttributeLocation(const std::string& name)
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

GLuint Program::getUniformLocation(const std::string& name)
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

void Program::use() const
{
	if(linked)
	{
		glUseProgram(id);
	}
	else
    {
        std::cerr << "Program: error using, program not linked" << std::endl;
    }
}

GLuint Program::getId() const
{
	return id;
}

bool  Program::isLinked() const
{
	return linked;
}

bool Program::isAttached(ShaderType type) const
{
	return (shaderIds[type] != -1);
}