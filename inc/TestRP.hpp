
#ifndef TESTRP_HPP
#define TESTTP_HPP

#include "Model3D.hpp"
#include "RenderProcedure.hpp"
#include "Shader.hpp"
#include "Program.hpp"

class TestRP : public RenderProcedure
{
public:

    TestRP(Texture* texture);
    ~TestRP();

    Texture* getTexture();


    void init(const RenderFrame& rf);
    void render(const RenderFrame& rf) const;

private:

    Model3D* plane;
    Texture* texture;
    Shader* vs;
    Shader* fs;
    Program* p;
};

#endif
