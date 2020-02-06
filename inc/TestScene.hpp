
#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include "Scene.hpp"
#include "App.hpp"

#include "RenderFrame.hpp"
#include "Scene3D.hpp"

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

    bool tp, bp, lp, rp;

    static void callback_cursor(GLFWwindow *window, double xpos, double ypos);
    static void callback_key(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void callback_resize(GLFWwindow *window, int width, int height);
};

#endif