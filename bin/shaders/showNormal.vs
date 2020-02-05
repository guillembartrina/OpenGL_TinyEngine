#version 450

layout(location = 0)in vec3 vertex;
layout(location = 1)in vec3 normal;
layout(location = 10)in vec3 ka;
layout(location = 11)in vec3 kd;
layout(location = 12)in vec3 ks;
layout(location = 13)in float ns;

out vec3 vnormal;
out vec3 vka;
out vec3 vkd;
out vec3 vks;
out float vns;

layout(location = 0)uniform mat4 MM;
layout(location = 1)uniform mat4 VM;
layout(location = 2)uniform mat4 PM;

void main()
{
	vka = ka;
	vkd = kd;
	vks = ks;
	vns = ns;

	mat3 NM = inverse(transpose(mat3(VM * MM)));
	vnormal = normalize(NM * normal);

	gl_Position = PM * VM * MM * vec4(vertex, 1.0);
}