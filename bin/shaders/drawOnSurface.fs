#version 450

//uniform sampler2D texture;

in vec2 vTexCoord;

layout(location = 10)uniform vec4 color;

void main()
{
    gl_FragColor = color;
}