
#ifndef TESTRP_HPP
#define TESTTP_HPP

#include "Model3D.hpp"
#include "RenderProcedure.hpp"

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
