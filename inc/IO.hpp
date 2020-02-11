
#ifndef IO_HPP
#define IO_HPP

#include <string>
#include <vector>

#include "Enums.hpp"

class IO 
{
public:
 
	static bool readFile(const std::string& path, std::string& src);

    static bool readOBJ(const std::string& path, std::vector<Model3DDefinition>& defs);

private:

    IO();
    ~IO();
};

#endif