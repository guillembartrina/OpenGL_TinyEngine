
#include "TestScene.hpp"

#include <iostream>

#include "Model3D.hpp"

TestScene::TestScene(App* app)
{
    GLFWwindow* window = app->getWindow();
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, callback_key);
	glfwSetCursorPosCallback(window, callback_cursor);
	glfwSetWindowSizeCallback(window, callback_resize);

    rf = new RenderFrame(glm::ivec2(0, 0), glm::uvec2(app->getW(), app->getH()));

    Camera* cam = new Camera();
    cam->setFocus(glm::vec3(0.0, 10.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -1.0));
    cam->setOptic_Perspective(PI/2.0, 1.0, 0.1, 40.0);
    scene.pushCamera(cam);

    scene.getLights().push_back(glm::vec3(5.0, 5.0, 0.0));
    scene.getLights().push_back(glm::vec3(-5.0, 5.0, 0.0));

    for(int i = -8; i <= 8; i++)
    {
        Model3D* cube = Model3D::cube("dd");
        cube->setSize(glm::vec3(1.0));
        cube->setPosition(glm::vec3(i, 0.0, 0.0));
        scene.getEntities().insert(scene.getEntities().end(), cube);
    }

    Model3D* cube = Model3D::cube("dd");
    cube->setSize(glm::vec3(20, 1, 1));
    cube->setPosition(glm::vec3(0.0, 2.5, 0.0));
    scene.getEntities().insert(scene.getEntities().end(), cube);

    tp = bp = lp = rp = false;
}

TestScene::~TestScene()
{
    delete rf;
}

void TestScene::update()
{
    if(tp) scene.getCamera()->move(glm::vec3(0.0, 0.0, -0.1));
    if(bp) scene.getCamera()->move(glm::vec3(0.0, 0.0, 0.1));
    if(lp) scene.getCamera()->move(glm::vec3(-0.1, 0.0, 0.0));
    if(rp) scene.getCamera()->move(glm::vec3(0.1, 0.0, 0.0));
}

void TestScene::draw() const
{
    rf->clean();
    scene.draw(*rf);
}

void TestScene::callback_cursor(GLFWwindow *window, double xpos, double ypos)
{
    TestScene* scene = static_cast<TestScene*>(glfwGetWindowUserPointer(window));

    double diffX = xpos - scene->rf->getSize().x/2;
    scene->scene.getCamera()->rotateX_VRP(-diffX / 360.f);

    double diffY = ypos - scene->rf->getSize().y/2;
    scene->scene.getCamera()->rotateY_VRP(-diffY / 360.f);

    glfwSetCursorPos(window, scene->rf->getSize().x/2, scene->rf->getSize().y/2);
}

void TestScene::callback_key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    TestScene* scene = static_cast<TestScene*>(glfwGetWindowUserPointer(window));

    if(action == GLFW_PRESS)
    {
        if(key == GLFW_KEY_UP) scene->tp = true;
        else if(key == GLFW_KEY_DOWN) scene->bp = true; 
        else if(key == GLFW_KEY_LEFT) scene->lp = true; 
        else if(key == GLFW_KEY_RIGHT) scene->rp = true; 
    }

    if(action == GLFW_RELEASE)
    {
        if(key == GLFW_KEY_UP) scene->tp = false;
        else if(key == GLFW_KEY_DOWN) scene->bp = false; 
        else if(key == GLFW_KEY_LEFT) scene->lp = false; 
        else if(key == GLFW_KEY_RIGHT) scene->rp = false; 
    }
}

void TestScene::callback_resize(GLFWwindow *window, int width, int height)
{
    TestScene* scene = static_cast<TestScene*>(glfwGetWindowUserPointer(window));
}
