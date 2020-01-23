
#ifndef APP_HPP
#define APP_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "Shader.hpp"
#include "Program.hpp"
#include "Camera.hpp"
#include "Model3D.hpp"
#include "Rectangle.hpp"
#include "RenderFrame.hpp"
#include "TestRP.hpp"

class App
{
public:

    App(const char* name, unsigned int W, unsigned int H);
    ~App();

    void run();

private:

    //local
    GLFWwindow* window;
    unsigned int W, H;

    //logic
    double timecount;

    Shader* vs;
    Shader* fs;
    Program* program;

    TestRP* trp;

    GLuint testRect;

    std::vector<Model3D*> drawables;
    Rectangle* rect;

    RenderFrame* rf;

    void update();

    void draw() const;

    void handleEvents();
    static void callback_key(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void callback_cursor(GLFWwindow *window, double xpos, double ypos);
    static void callback_resize(GLFWwindow *window, int width, int height);

};

#endif