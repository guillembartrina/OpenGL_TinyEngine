
#ifndef MODEL3DM_HPP
#define MODEL3DM_HPP

#include "IO.hpp"
#include "Enums.hpp"
#include "Entity3D.hpp"

class Model3DM : public Entity3D
{
public:

    Model3DM(const std::vector<Model3DDefinition>& m3ds);
    ~Model3DM();

protected:

private:

    void specificDraw() const;

    struct Model3DProperties
    {
        GLuint VAO;
        std::vector<GLuint> VBOs;
        bool indexed;
        unsigned int elements;
        const Texture* texture;
        bool blending;
    };

    std::vector<Model3DProperties> models;
    
};

#endif