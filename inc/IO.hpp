
#ifndef IO_HPP
#define IO_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

struct DrawableDefinition
{
    DrawableDefinition() {}
    ~DrawableDefinition() {}
    
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

class IO 
{
public:
 
	static bool readFile(const std::string& path, std::string& src);

    static bool readOBJ(const std::string& path, std::vector<DrawableDefinition>& defs);

private:

    IO();
    ~IO();
};

#endif