
#ifndef RENDERPROCEDURE_HPP
#define RENDERPROCEDURE_HPP

#include "RenderFrame.hpp"

class RenderFrame;

class RenderProcedure
{
public:

    virtual void render(const RenderFrame& rf) const = 0;
};

#endif