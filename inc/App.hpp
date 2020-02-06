
#ifndef APP_HPP
#define APP_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Scene.hpp"

class App
{
public:

    App(const char* name, unsigned int W, unsigned int H);
    ~App();

    void run();

    unsigned int getW() const;
    unsigned int getH() const;
    GLFWwindow* getWindow();

private:

    unsigned int W, H;
    GLFWwindow* window;

    double timecount;
};

#endif