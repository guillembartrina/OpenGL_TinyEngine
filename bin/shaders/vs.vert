#version 450

layout(location = 0)in vec3 vertex;
layout(location = 1)in vec3 normal;
layout(location = 2)in vec2 texCoord;
layout(location = 10)in vec3 ka;
layout(location = 11)in vec3 kd;
layout(location = 12)in vec3 ks;
layout(location = 13)in float ns;

out vec3 positionF;
out vec3 normalF;
out vec3 kaF;
out vec3 kdF;
out vec3 ksF;
out float nF;

out vec3 focusF;

layout(location = 0)uniform mat4 MM;
layout(location = 1)uniform mat4 VM;
layout(location = 2)uniform mat4 PM;

uniform bool SCOfocus;
uniform vec3 focus;

void main()
{
	positionF = (VM * MM * vec4(vertex, 1.0)).xyz;

	mat3 NM = inverse(transpose(mat3(VM * MM)));
	normalF = normalize(NM * normal);

	kaF = ka;
	kdF = kd;
	ksF = ks;
	nF = ns;

	if(SCOfocus) focusF = focus;
	else focusF = (VM * vec4(focus, 1.0)).xyz;

	gl_Position = PM * VM * MM * vec4(vertex, 1.0);
}