
#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include "Scene.hpp"
#include "App.hpp"

#include "RenderFrame.hpp"
#include "Scene3D.hpp"
#include "Rectangle.hpp"

class App;

class TestScene : public Scene
{
public:

    TestScene(App* app);
    ~TestScene();

    void update();
    void draw() const;

private:

    RenderFrame* rf;

    Scene3D scene;

    bool up_pressed, down_pressed, left_pressed, right_pressed;

    bool l_pressed, k_pressed;

    Texture* shadowMap;

    Shader* smvs,* smfs;
    Program* smp;
    
    static void callback_cursor(GLFWwindow *window, double xpos, double ypos);
    static void callback_key(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void callback_resize(GLFWwindow *window, int width, int height);
};

#endif