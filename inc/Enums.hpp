
#ifndef ENUMS_HPP
#define ENUMS_HPP

#include <string>
#include <utility>
#include <vector>

#include "GLM/vec3.hpp"

//--------------------------------

#define PI 3.14159265358979323846

//--------------------------------

typedef std::pair<glm::vec3,glm::vec3> BB;

struct Model3DDefinition
{
    Model3DDefinition() {}
    ~Model3DDefinition() {}
    
    std::vector<unsigned int> indices;
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::string texName;
    std::vector<float> kas;
    std::vector<float> kds;
    std::vector<float> kss;
    std::vector<float> nss;
};

inline BB computeBB(const Model3DDefinition& m3d)
{
	const std::vector<unsigned int>& I = m3d.indices;
	const std::vector<float>& V = m3d.vertices;

	glm::vec3 min, max;

	if(not I.empty())
	{
		min.x = max.x = V[I[0]+0];
		min.y = max.y = V[I[0]+1];
		min.z = max.z = V[I[0]+2];

		for(unsigned int i = 1; i < I.size(); i++)
		{
			glm::vec3 val = glm::vec3(V[3*I[i]+0], V[3*I[i]+1], V[3*I[i]+2]);
			if (val.x < min.x) min.x = val.x;
			if (val.x > max.x) max.x = val.x;
			if (val.y < min.y) min.y = val.y;
			if (val.y > max.y) max.y = val.y;
			if (val.z < min.z) min.z = val.z;
			if (val.z > max.z) max.z = val.z;
		}
	}
	else
	{
		min.x = max.x = V[0+0];
		min.y = max.y = V[0+1];
		min.z = max.z = V[0+2];

		for(unsigned int i = 3; i < V.size(); i+=3)
		{
			glm::vec3 val = glm::vec3(V[i+0], V[i+1], V[i+2]);
			if (val.x < min.x) min.x = val.x;
			if (val.x > max.x) max.x = val.x;
			if (val.y < min.y) min.y = val.y;
			if (val.y > max.y) max.y = val.y;
			if (val.z < min.z) min.z = val.z;
			if (val.z > max.z) max.z = val.z;
		}
	}
	return std::make_pair(min, max);
}

struct Light
{
    glm::vec3 position;
    glm::vec3 color;

    Light(glm::vec3 position, glm::vec3 color = glm::vec3(1.0, 1.0, 1.0)) : position(position), color(color) {}
};

//--------------------------------

enum SAL3D
{
    SAL3D_vertex = 0,
    SAL3D_normal = 1,
    SAL3D_texCoord = 2,
    SAL3D_ka = 10,
    SAL3D_kd = 11,
    SAL3D_ks = 12,
    SAL3D_ns = 13,
    SAL3D_NUM = 7
};

enum SUL3D
{
    SUL3D_MM = 0,
    SUL3D_VM = 1,
    SUL3D_PM = 2,
    SUL3D_textured = 10,
    SUL3D_numLights = 20,
    SUL3D_lights = 21,
    SUL3D_NUM = 5
};


enum SAL2D
{
    SAL2D_vertex = 0,
    SAL2D_texCoord = 1,
    SAL2D_NUM = 2
};

enum SUL2D
{
    SUL2D_MM = 0,
    SUL2D_WM = 1,
    SUL2D_textured = 10,
    SUL2D_color = 20,
    SUL2D_NUM = 4
};

#endif