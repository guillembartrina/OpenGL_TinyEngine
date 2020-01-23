
#include "Model3D.hpp"

#include <iostream>

Model3D::Model3D(const DrawableDefinition& dd)
{
	indexed = false;

    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint tmpVBO;

	if(not dd.indices.empty())
	{
		indexed = true;
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * dd.indices.size(), &dd.indices[0], GL_STATIC_DRAW);
	}

	if(not dd.vertices.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * dd.vertices.size(), &dd.vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL::vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL::vertex);
	}

	if(not dd.normals.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * dd.normals.size(), &dd.normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL::normal, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL::normal);
	}

	if(not dd.texCoords.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * dd.texCoords.size(), &dd.texCoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL::texCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL::texCoord);
	}

	if(not dd.kas.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * dd.kas.size(), &dd.kas[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL::ka, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL::ka);
	}

	if(not dd.kds.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * dd.kds.size(), &dd.kds[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL::kd, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL::kd);
	}

	if(not dd.kss.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * dd.kss.size(), &dd.kss[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL::ks, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL::ks);
	}

	if(not dd.nss.empty())
	{
		glGenBuffers(1, &tmpVBO);
		VBOs.push_back(tmpVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * dd.nss.size(), &dd.nss[0], GL_STATIC_DRAW);
		glVertexAttribPointer(SAL::ns, 1, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SAL::ns);
	}

	glBindVertexArray(0);

	elements = (indexed ? dd.indices.size() : dd.vertices.size());

	bb = computeBB(dd);
	center = (bb.first + bb.second) / 2.f;
}

Model3D::~Model3D()
{
	glDeleteBuffers(VBOs.size(), &VBOs[0]);
	glDeleteVertexArrays(1, &VAO);
}

void Model3D::draw() const
{
	glBindVertexArray(VAO);
	Transformable3D::bind();
	if(indexed)
	{
		glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, elements);
	}
	glBindVertexArray(0);
}

Model3D* Model3D::plane()
{
	DrawableDefinition dd;
    dd.vertices = { 0.0,    0.0,    0.0,
                    1.0,    0.0,	0.0,
                    0.0,   	1.0,    0.0,
                    1.0,    1.0,    0.0 };

    dd.indices = {  1,  2,  0,
                    1,  3,  2 };

	return new Model3D(dd);
}

Model3D* Model3D::cube()
{
	DrawableDefinition dd;
    dd.vertices = { 0.0, 0.0, 0.0, //0
                    0.0, 0.0, 1.0, //1
                    0.0, 1.0, 0.0, //2
                    0.0, 1.0, 1.0, //3
                    1.0, 0.0, 0.0, //4
                    1.0, 0.0, 1.0, //5
                    1.0, 1.0, 0.0, //6
                    1.0, 1.0, 1.0 };

    dd.indices = {  0,  6,  4,
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

	return new Model3D(dd);
}

BB Model3D::computeBB(const DrawableDefinition& dd)
{
	const std::vector<unsigned int>& I = dd.indices;
	const std::vector<float>& V = dd.vertices;

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