
#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <utility>
#include <vector>

#include "GL/glew.h"

#include "Shader.hpp"

class Program //NEEDS OPENGL CONTEXT
{
public:

	Program();
	~Program();

	void attachShader(const Shader& shader);

	void defineAttributesLocation(const std::vector<std::pair<std::string, GLuint>>& data);

	GLuint getAttributeLocation(const std::string& name);
	GLuint getUniformLocation(const std::string& name);

	bool link();

	void use() const;

	GLuint getId() const;

	bool isLinked() const;
	bool isAttached(ShaderType type) const;

private:

	GLuint id;
	GLuint shaderIds[ShaderType::ShaderType_NUM];

	bool linked;
};

#endif
	
