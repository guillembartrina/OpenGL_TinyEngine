
#include "App.hpp"

#include <iostream>

#include "IO.hpp"
#include "Model3D.hpp"

#define printWarning(x) (std::cout<<"> Warning: "<<x<<std::endl)

#define PI 3.14159265358979323846

App::App(const char* name, unsigned int W, unsigned int H)
{
    if(!glfwInit()) throw std::runtime_error("Failed to init GLFW");

    this->W = W;
    this->H = H;

    window = glfwCreateWindow(W, H, name, NULL, NULL);
    if(!window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create window");
	}

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(window, W/2, H/2);

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, callback_key);
	glfwSetCursorPosCallback(window, callback_cursor);
	glfwSetWindowSizeCallback(window, callback_resize);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);

    glewInit();

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    rf = new RenderFrame(glm::vec2(0, 0), glm::vec2(W, H));

    //---

    //rf->camera.applyResize(W, H);

    texture = new Texture("textures/cat.jpg");
    Texture* dd = new Texture(W, H, FBComponent_Color);

    //---
    drawables.push_back(Model3D::cube());
    drawables.back()->setOrigin(glm::vec3(0.0, 1.0, 0.0));
    drawables.back()->setSize(glm::vec3(10.0, 1.0, 10.0));
    drawables.back()->setPosition(glm::vec3(5.0, 0.0, 5.0));

    std::vector<Model3DDefinition> dds;
    if(not IO::readOBJ("objs/Crate1.obj", dds))
    {
        std::cerr << "ERROR LOADING OBJ" << std::endl;
    }

    for(int i = 0; i < 10; i++)
    {
        for(Model3DDefinition& dd : dds)
        {
            drawables.push_back(new Model3D(dd));
            drawables.back()->setSize(glm::vec3(1, 1, 1));
            drawables.back()->setPosition(glm::vec3(0.5 + i, 0.0, 0.5));
        }
    }

    rf->getCamera()->setFocus(glm::vec3(5.0, 10.0, 5.0), glm::vec3(5.0, 0.0, 5.0), glm::vec3(0.0, 0.0, -1.0));
    rf->getCamera()->setOptic_Perspective(90.f * (3.1415926535 / 180.0), 1.0, 0.1, 40.0);

    rf->getLights().push_back(glm::vec3(5.0, 5.0, 5.0));

    rf->startDrawing();
    for(int i = 0; i < drawables.size(); i++)
    {
        rf->draw(*drawables[i]);
    }
    rf->endDrawing();

    rf->sampleTexture(dd);

    rect = new Rectangle(glm::vec2(W/2, H/2), glm::vec2(100, 100), texture);
}

App::~App()
{
    for(unsigned int i = 0; i < drawables.size(); i++)
    {
        delete drawables[i];
    }

    delete texture;
    delete rf;
    delete rect;

    glfwDestroyWindow(window);
    glfwTerminate();
}

void App::run()
{
    timecount = glfwGetTime();

    while(!glfwWindowShouldClose(window))
    {
        update();
        handleEvents();
        draw();

        while (glfwGetTime() < (timecount + 1.0/60.0));
		timecount += 1.0/60.0;
    }
}

void App::update()
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        rf->getCamera()->move(glm::vec3(0.0, 0.0, -0.1));
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        rf->getCamera()->move(glm::vec3(0.0, 0.0, 0.1));
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        rf->getCamera()->move(glm::vec3(-0.1, 0.0, 0.0));
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        rf->getCamera()->move(glm::vec3(0.1, 0.0, 0.0));
    }
}

void App::draw() const
{   
    rf->startDrawing();
    for(int i = 0; i < drawables.size(); i++)
    {
        rf->draw(*drawables[i]);
    }
    rf->drawOnSurface(*rect);
    rf->endDrawing();

    glfwSwapBuffers(window);
}

void App::handleEvents()
{
    glfwPollEvents();
}

void App::callback_key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));

    if(action == GLFW_RELEASE) return;

    if(GLFW_KEY_W == key)
    {
        //rf->getCamera()->move(glm::vec3(0.0, 0.0, -0.1));
        app->drawables[10]->translate(glm::vec3(0, 0, -1));
    }

    if(GLFW_KEY_S == key)
    {
        //rf->getCamera()->move(glm::vec3(0.0, 0.0, 0.1));
        app->drawables[10]->translate(glm::vec3(0, 0, 1));
    }

    if(GLFW_KEY_A == key)
    {
        //rf->getCamera()->move(glm::vec3(-0.1, 0.0, 0.0));
        app->drawables[10]->translate(glm::vec3(-1, 0, 0));
    }

    if(GLFW_KEY_D == key)
    {
        //rf->getCamera()->move(glm::vec3(0.1, 0.0, 0.0));
        app->drawables[10]->translate(glm::vec3(1, 0, 0));
    }

    if(GLFW_KEY_N == key)
    {
        //rf->getCamera()->move(glm::vec3(0.1, 0.0, 0.0));
        app->drawables[10]->rotateY(PI/4.f);
    }

    if(GLFW_KEY_M == key)
    {
        //rf->getCamera()->move(glm::vec3(0.1, 0.0, 0.0));
        app->drawables[10]->rotateZ(PI/4.f);
    }
}

void App::callback_cursor(GLFWwindow *window, double xpos, double ypos)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));

    double diffX = xpos - app->W/2;
    app->rf->getCamera()->rotateX_VRP(-diffX / 360.f);

    double diffY = ypos - app->H/2;
    app->rf->getCamera()->rotateY_VRP(-diffY / 360.f);

    glfwSetCursorPos(window, app->W/2, app->H/2);
}

void App::callback_resize(GLFWwindow *window, int width, int height)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));

    //app->W = width;
	//app->H = height;

	//app->rf->camera.applyResize(width, height);
}