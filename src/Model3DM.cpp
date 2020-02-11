
#include "Model3DM.hpp"

#include <iostream>

#include "Program.hpp"

Model3DM::Model3DM(const std::vector<Model3DDefinition>& m3ds)
{
	bb = std::make_pair(glm::vec3(std::numeric_limits<float>::max()), glm::vec3(std::numeric_limits<float>::min()));

	for(int i = 0; i < m3ds.size(); i++)
	{
		Model3DProperties model;

		model.indexed = false;

		glGenVertexArrays(1, &model.VAO);
		glBindVertexArray(model.VAO);

		GLuint tmpVBO;

		if(not m3ds[i].indices.empty())
		{
			model.indexed = true;
			glGenBuffers(1, &tmpVBO);
			model.VBOs.push_back(tmpVBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmpVBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m3ds[i].indices.size(), &m3ds[i].indices[0], GL_STATIC_DRAW);
		}

		if(not m3ds[i].vertices.empty())
		{
			glGenBuffers(1, &tmpVBO);
			model.VBOs.push_back(tmpVBO);
			glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3ds[i].vertices.size(), &m3ds[i].vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(SAL3D_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(SAL3D_vertex);
		}

		if(not m3ds[i].normals.empty())
		{
			glGenBuffers(1, &tmpVBO);
			model.VBOs.push_back(tmpVBO);
			glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3ds[i].normals.size(), &m3ds[i].normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(SAL3D_normal, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(SAL3D_normal);
		}

		if(not m3ds[i].texCoords.empty())
		{
			glGenBuffers(1, &tmpVBO);
			model.VBOs.push_back(tmpVBO);
			glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3ds[i].texCoords.size(), &m3ds[i].texCoords[0], GL_STATIC_DRAW);
			glVertexAttribPointer(SAL3D_texCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(SAL3D_texCoord);

			if(not m3ds[i].texName.empty()) model.texture = new Texture(m3ds[i].texName);
		}

		if(not m3ds[i].kas.empty())
		{
			glGenBuffers(1, &tmpVBO);
			model.VBOs.push_back(tmpVBO);
			glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3ds[i].kas.size(), &m3ds[i].kas[0], GL_STATIC_DRAW);
			glVertexAttribPointer(SAL3D_ka, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(SAL3D_ka);
		}

		if(not m3ds[i].kds.empty())
		{
			glGenBuffers(1, &tmpVBO);
			model.VBOs.push_back(tmpVBO);
			glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3ds[i].kds.size(), &m3ds[i].kds[0], GL_STATIC_DRAW);
			glVertexAttribPointer(SAL3D_kd, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(SAL3D_kd);
		}

		if(not m3ds[i].kss.empty())
		{
			glGenBuffers(1, &tmpVBO);
			model.VBOs.push_back(tmpVBO);
			glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3ds[i].kss.size(), &m3ds[i].kss[0], GL_STATIC_DRAW);
			glVertexAttribPointer(SAL3D_ks, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(SAL3D_ks);
		}

		if(not m3ds[i].nss.empty())
		{
			glGenBuffers(1, &tmpVBO);
			model.VBOs.push_back(tmpVBO);
			glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m3ds[i].nss.size(), &m3ds[i].nss[0], GL_STATIC_DRAW);
			glVertexAttribPointer(SAL3D_ns, 1, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(SAL3D_ns);
		}

		glBindVertexArray(0);

		model.blending = false;

		model.elements = (model.indexed ? m3ds[i].indices.size() : m3ds[i].vertices.size());

		BB tmpbb = computeBB(m3ds[i]);

		if (tmpbb.first.x < bb.first.x) bb.first.x = tmpbb.first.x;
		if (tmpbb.second.x > bb.second.x) bb.second.x = tmpbb.second.x;
		if (tmpbb.first.y < bb.first.y) bb.first.y = tmpbb.first.y;
		if (tmpbb.second.y > bb.second.y) bb.second.y = tmpbb.second.y;
		if (tmpbb.first.z < bb.first.z) bb.first.z = tmpbb.first.z;
		if (tmpbb.second.z > bb.second.z) bb.second.z = tmpbb.second.z;

		models.push_back(model);
	}

	position = (bb.first+bb.second)/2.f;
	size = (bb.second-bb.first);

	MMOutOfDate = true;
}

Model3DM::~Model3DM()
{
	for(int i = 0; i < models.size(); i++)
	{
		glDeleteBuffers(models[i].VBOs.size(), &models[i].VBOs[0]);
		glDeleteVertexArrays(1, &models[i].VAO);
	}
}

void Model3DM::specificDraw() const
{
	for(int i = 0; i < models.size(); i++)
	{
		if(models[i].blending) glEnable(GL_BLEND);
    	else glDisable(GL_BLEND);

		glBindVertexArray(models[i].VAO);
		Program::getActiveProgram()->setUniformValue(SUL2D_textured, (models[i].texture ? GL_TRUE : GL_FALSE));
		if(models[i].texture) models[i].texture->bind();

		if(models[i].indexed)
		{
			glDrawElements(GL_TRIANGLES, models[i].elements, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, models[i].elements);
		}
	}
}