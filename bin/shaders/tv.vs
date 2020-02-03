#version 450

layout(location = 0)in vec3 vertex;
layout(location = 2)in vec2 texCoord;

out vec3 vtexCoord;

void main()
{
	vtexCoord = texCoord;
	gl_Position = vec4(vertex, 1.0);
}