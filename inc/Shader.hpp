
#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include "GL/glew.h"

enum ShaderType
{
	Vertex = 0,
	Geomerty,
	Fragment,
	ShaderType_NUM
};

class Shader //NEEDS OPENGL CONTEXT
{
public:

	Shader(ShaderType type);
	~Shader();

	void load_default();
	void load_fromString(const std::string& source);
	bool load_fromFile(const std::string& path);

	bool compile();

	ShaderType getType() const;
	GLuint getId() const;

	bool isLoaded() const;
	bool isCompiled() const;

private:

	ShaderType type;
	GLuint id;

	bool loaded;
	bool compiled;

	static const std::string defaultShaders[ShaderType::ShaderType_NUM];
};

#endif