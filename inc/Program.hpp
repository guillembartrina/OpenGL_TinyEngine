
#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <utility>
#include <vector>

#include "GL/glew.h"
#include "GLM/glm.hpp"

#include "Shader.hpp"

class Program //NEEDS OPENGL CONTEXT
{
public:

	Program();
	~Program();

	void attachShader(const Shader& shader);

	void defineAttributesLocation(const std::vector<std::pair<std::string, GLuint>>& data);

	bool link();

	GLuint getAttributeLocation(const std::string& name) const;
	GLuint getUniformLocation(const std::string& name) const;

	GLuint getId() const;

	void use() const;

	void setUniformValue(GLuint location, int value) const;
	void setUniformValue(GLuint location, float value) const;
	void setUniformValue(GLuint location, const glm::vec2& value) const;
	void setUniformValue(GLuint location, const glm::vec3& value) const;
	void setUniformValue(GLuint location, const glm::vec4& value) const;
	void setUniformValue(GLuint location, const glm::mat3& value) const;
	void setUniformValue(GLuint location, const glm::mat4& value) const;
	void setUniformValue(GLuint location, const std::vector<glm::vec3>& value) const;

	bool isLinked() const;
	bool isAttached(ShaderType type) const;

	static const Program* getActiveProgram();
	static const Program* getDefaultDrawProgram();
	static const Program* getDefaultDrawOnSurfaceProgram();

private:

	GLuint id;
	GLuint shaderIds[ShaderType_NUM];

	bool linked;

	static const Program* activeProgram;

    static Shader* drawVS;
    static Shader* drawFS;
    static Program* drawProgram;
	static Shader* drawOnSurfaceVS;
    static Shader* drawOnSurfaceFS;
    static Program* drawOnSurfaceProgram;
};

#endif
	
