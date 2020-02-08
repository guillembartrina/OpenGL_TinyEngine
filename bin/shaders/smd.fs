#version 450

#define MAX_LIGHTS 32

in vec3 vvertex;
in vec3 vnormal;
in vec2 vtexCoord;
in vec3 vka;
in vec3 vkd;
in vec3 vks;
in float vns;

in vec4 lvertex;

out vec4 fragColor;

layout(location = 1)uniform mat4 VM;
layout(location = 10)uniform bool textured;
layout(location = 20)uniform int numLights;
layout(location = 21)uniform vec3 lights[MAX_LIGHTS];

layout(binding = 0)uniform sampler2D tex;
layout(binding = 1)uniform sampler2D shadowMap;

vec3 Ambient()
{
    return max(vka, vkd*0.1f);
}

vec3 Diffuse(vec3 light)
{
    vec3 col = vec3(0.0, 0.0, 0.0);
    vec3 L = normalize(light - vvertex);
    float alpha = dot(vnormal, L);

    if(alpha > 0)
    {
        col = vkd * alpha;
    }

    return (col);
}

vec3 Specular(vec3 light)
{
    vec3 col = vec3(0.0, 0.0, 0.0);
    vec3 L = normalize(light - vvertex);
    float alpha = dot(vnormal, L);

    if(alpha > 0)
    {
        vec3 R = reflect(-L, vnormal);
        vec3 V = normalize(-vvertex);
        float beta = dot(R, V);
        if(beta > 0 && vns > 0.0)
        {
            float shine = pow(max(0.0, beta), vns);
            col = vks * shine;
        }
    }
    return (col);
}

void main()
{
    vec3 color;
    color = Ambient();

    vec2 st = lvertex.st/lvertex.q;
    float trueDepth = lvertex.p/lvertex.q;
    float storedDepth = texture(shadowMap, st).r;

    if(trueDepth - 0.001 <= storedDepth)
    {
        for(int i = 0; i < numLights; i++)
        {
            vec3 light = (VM * vec4(lights[i], 1.0)).xyz;
            color += (Diffuse(light) + Specular(light));
        }
    }

    if(textured) fragColor = texture(tex, vtexCoord) * vec4(color, 1.0);
    else fragColor = vec4(color, 1.0);
}