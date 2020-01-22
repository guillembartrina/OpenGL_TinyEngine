
#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "GL/glew.h"

#include "Enums.hpp"
#include "RenderFrame.hpp"
#include "RenderProcedure.hpp"

class RenderFrame;

class Drawable
{
private:

    friend class RenderFrame;
    friend class RenderProcedure;

    virtual void draw() const = 0;   
};

#endif