
#include "IO.hpp"

#include <fstream>
#include <sstream>

#include "OBJ_Loader.hpp"

IO::IO() {}
IO::~IO() {}

bool IO::readFile(const std::string& path, std::string& src)
{
    src.clear();
	std::ifstream file(path);
	if (file.is_open())
	{
		std::stringstream ss;
		ss << file.rdbuf();
		src = ss.str();
		file.close();
		return true;
	}
	return false;
}

bool IO::readOBJ(const std::string& path, std::vector<Model3DDefinition>& defs)
{
	defs.clear();

	objl::Loader loader;
	bool ok = loader.LoadFile(path);

	if(not ok) return false;

	for(unsigned int i = 0; i < loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh& mesh = loader.LoadedMeshes[i];

		defs.push_back(Model3DDefinition());
		Model3DDefinition& dd = defs.back();

		dd.indices = mesh.Indices;

		for(int i = 0; i < mesh.Vertices.size(); i++)
		{
			dd.vertices.push_back(mesh.Vertices[i].Position.X);
			dd.vertices.push_back(mesh.Vertices[i].Position.Y);
			dd.vertices.push_back(mesh.Vertices[i].Position.Z);

			dd.normals.push_back(mesh.Vertices[i].Normal.X);
			dd.normals.push_back(mesh.Vertices[i].Normal.Y);
			dd.normals.push_back(mesh.Vertices[i].Normal.Z);

			dd.texCoords.push_back(mesh.Vertices[i].TextureCoordinate.X);
			dd.texCoords.push_back(mesh.Vertices[i].TextureCoordinate.Y);

			dd.kas.push_back(mesh.MeshMaterial.Ka.X);
			dd.kas.push_back(mesh.MeshMaterial.Ka.Y);
			dd.kas.push_back(mesh.MeshMaterial.Ka.Z);

			dd.kds.push_back(mesh.MeshMaterial.Kd.X);
			dd.kds.push_back(mesh.MeshMaterial.Kd.Y);
			dd.kds.push_back(mesh.MeshMaterial.Kd.Z);

			dd.kss.push_back(mesh.MeshMaterial.Ks.X);
			dd.kss.push_back(mesh.MeshMaterial.Ks.Y);
			dd.kss.push_back(mesh.MeshMaterial.Ks.Z);

			dd.nss.push_back(mesh.MeshMaterial.Ns);
		}

		dd.texName = mesh.MeshMaterial.map_Kd;
	}

	return true;
}