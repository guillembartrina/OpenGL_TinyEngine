
#ifndef TESTRP_HPP
#define TESTTP_HPP

#include "RenderProcedure.hpp"
#include "Model3D.hpp"

class TestRP : public RenderProcedure
{
public:

    TestRP();
    ~TestRP();

    void render() const;

private:

    Model3D* cube;
};

#endif
