
#include "IO.hpp"

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

static bool readOBJ(const std::string& path, DrawableDefinition& def)
{
	return false;
}