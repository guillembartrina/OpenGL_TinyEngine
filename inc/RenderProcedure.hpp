
#ifndef RENDERPROCEDURE_HPP
#define RENDERPROCEDURE_HPP

#include "RenderFrame.hpp"

class RenderFrame;

class RenderProcedure
{
public:

    virtual void init(RenderFrame& rf) = 0;
    virtual void render(RenderFrame& rf) = 0;
};

#endif