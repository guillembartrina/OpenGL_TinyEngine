
#ifndef RENDERPROCEDURE_HPP
#define RENDERPROCEDURE_HPP

#include "RenderFrame.hpp"

class RenderFrame;

class RenderProcedure
{
public:

    virtual void init(const RenderFrame& rf) = 0;
    virtual void render(const RenderFrame& rf) const = 0;
};

#endif