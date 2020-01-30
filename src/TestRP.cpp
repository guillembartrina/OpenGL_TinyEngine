
#include "TestRP.hpp"

TestRP::TestRP()
{
    Model3DDefinition dd;
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

    cube = new Model3D(dd);
}

TestRP::~TestRP()
{
    delete cube;
}

void TestRP::render() const
{
    cube->draw();
}