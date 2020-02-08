#version 450

in vec3 vnormal;
in vec3 vka;
in vec3 vkd;
in vec3 vks;
in float vns;

out vec4 fragColor;

void main()
{
    fragColor = vec4(vnormal, 1.0);
}