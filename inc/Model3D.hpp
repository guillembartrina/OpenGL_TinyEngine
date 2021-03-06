
#ifndef MODEL3D_HPP
#define MODEL3D_HPP

#include "IO.hpp"
#include "Enums.hpp"
#include "Entity3D.hpp"

class Model3D : public Entity3D
{
public:

    Model3D(const Model3DDefinition& m3d);
    ~Model3D();

    static Model3D* plane(const std::string& texName);
    static Model3D* cube(const std::string& texName);

protected:

private:

    void specificDraw() const;
    
    std::vector<GLuint> VBOs;

    bool indexed;
    unsigned int elements;
};

#endif