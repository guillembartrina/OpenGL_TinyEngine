#version 450

layout(location = 0)in vec3 vertex;
layout(location = 1)in vec3 normal;
layout(location = 2)in vec2 texCoord;
layout(location = 10)in vec3 ka;
layout(location = 11)in vec3 kd;
layout(location = 12)in vec3 ks;
layout(location = 13)in float ns;

out vec3 vvertex;
out vec3 vnormal;
out vec2 vtexCoord;
out vec3 vka;
out vec3 vkd;
out vec3 vks;
out float vns;

out vec4 lvertex;

layout(location = 0)uniform mat4 MM;
layout(location = 1)uniform mat4 VM;
layout(location = 2)uniform mat4 PM;
layout(location = 3)uniform mat4 LVM;
layout(location = 4)uniform mat4 LPM;

void main()
{
    mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,  0.0, 1.0, 0.0, 0.0,  0.0, 0.0, 1.0, 0.0,  0.5, 0.5, 0.5, 1.0);
    mat4 scal = mat4(0.5, 0.0, 0.0, 0.0,  0.0, 0.5, 0.0, 0.0,  0.0, 0.0, 0.5, 0.0,  0.0, 0.0, 0.0, 1.0);

    vvertex = (VM * MM * vec4(vertex, 1.0)).xyz;
    lvertex =  trans * scal * LPM * LVM * MM * vec4(vertex, 1.0);

    mat3 NM = inverse(transpose(mat3(VM * MM)));
    vnormal = normalize(NM * normal);

    vtexCoord = texCoord;
    vka = ka;
    vkd = kd;
    vks = ks;
    vns = ns;

    gl_Position = PM * VM * MM * vec4(vertex, 1.0);
}