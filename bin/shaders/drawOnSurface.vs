#version 450

layout(location = 0)in vec3 vertex;
layout(location = 1)in vec2 texCoord;

out vec2 vTexCoord;

layout(location = 0)uniform mat4 MM;
layout(location = 1)uniform mat4 SM;

void main()
{
    vTexCoord = texCoord;
	gl_Position = SM * MM * vec4(vertex, 1.0);
}