#version 450

layout(binding = 0)uniform sampler2D tex;

in vec2 vtexCoord;

void main()
{
    fragColor = texture(tex, vtexCoord);
}