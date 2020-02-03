
#include "Model3D.hpp"

#include <iostream>

Model3D::Model3D(const Model3DDefinition& m3d)
{
	indexed = false;

    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint tmpVBO;

	if(not m3d.indices.empty())
	{
		indexed = true;
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m3d.indices.size(), &m3d.indices[0], GL_STATIC_DRAW);
	}

	if(not m3d.vertices.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3d.vertices.size(), &m3d.vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL3D_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL3D_vertex);
	}

	if(not m3d.normals.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3d.normals.size(), &m3d.normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL3D_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL3D_normal);
	}

	if(not m3d.texCoords.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3d.texCoords.size(), &m3d.texCoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL3D_texCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL3D_texCoord);

		texture = new Texture(m3d.texName);
	}

	if(not m3d.kas.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3d.kas.size(), &m3d.kas[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL3D_ka, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL3D_ka);
	}

	if(not m3d.kds.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3d.kds.size(), &m3d.kds[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL3D_kd, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL3D_kd);
	}

	if(not m3d.kss.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3d.kss.size(), &m3d.kss[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL3D_ks, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL3D_ks);
	}

	if(not m3d.nss.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3d.nss.size(), &m3d.nss[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL3D_ns, 1, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL3D_ns);
	}

	glBindVertexArray(0);

	elements = (indexed ? m3d.indices.size() : m3d.vertices.size());

	bb = computeBB(m3d);

	position = (bb.first+bb.second)/2.f;
    size = (bb.second-bb.first);
    MMOutOfDate = true;
}

Model3D::~Model3D()
{
	glDeleteBuffers(VBOs.size(), &VBOs[0]);
	glDeleteVertexArrays(1, &VAO);
}

Model3D* Model3D::plane()
{
	Model3DDefinition m3d;
    m3d.vertices = {0.0,    0.0,    0.0,
                    1.0,    0.0,	0.0,
                    0.0,   	1.0,    0.0,
                    1.0,    1.0,    0.0 };
	
	m3d.normals = { 0.0,    0.0,    1.0,
                    0.0,    0.0,    1.0,
                    0.0,    0.0,    1.0,
                    0.0,    0.0,    1.0 };
					
	m3d.kds = { 	0.5,    0.5,    0.5,
                    0.5,    0.5,	0.5,
                    0.5,   	0.5,    0.5,
                    0.5,    0.5,    0.5 };

    m3d.indices = { 1,  2,  0,
                    1,  3,  2 };

	return new Model3D(m3d);
}

Model3D* Model3D::cube()
{
	Model3DDefinition m3d;
    m3d.vertices = {0.0, 0.0, 0.0, //0
                    0.0, 0.0, 1.0, //1
                    0.0, 1.0, 0.0, //2
                    0.0, 1.0, 1.0, //3
                    1.0, 0.0, 0.0, //4
                    1.0, 0.0, 1.0, //5
                    1.0, 1.0, 0.0, //6
                    1.0, 1.0, 1.0 };
	
	m3d.normals = { -1.0, -1.0, -1.0, //0
                    -1.0, -1.0, 1.0, //1
                    -1.0, 1.0, -1.0, //2
                    -1.0, 1.0, 1.0, //3
                    1.0, -1.0, -1.0, //4
                    1.0, -1.0, 1.0, //5
                    1.0, 1.0, -1.0, //6
                    1.0, 1.0, 1.0 };

	m3d.kds = { 	0.5, 0.5, 0.5, //0
                    0.5, 0.5, 0.5, //1
                    0.5, 0.5, 0.5, //2
                    0.5, 0.5, 0.5, //3
                    0.5, 0.5, 0.5, //4
                    0.5, 0.5, 0.5, //5
                    0.5, 0.5, 0.5, //6
                    0.5, 0.5, 0.5 };

    m3d.indices = { 0,  6,  4,
                    0,  2,  6,
                    1,  2,  0,
                    1,  3,  2,
                    5,  3,  1,
                    5,  7,  3,
                    4,  7,  5,
                    4,  6,  7,
                    4,  1,  0,
                    4,  6,  1,
                    7,  2,  3,
                    7,  6,  2 };

	return new Model3D(m3d);
}

void Model3D::specificDraw() const
{
	if(indexed)
	{
		glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, elements);
	}
}

BB Model3D::computeBB(const Model3DDefinition& m3d)
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