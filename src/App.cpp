
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

    snvs = new Shader(ShaderType_Vertex);
    snvs->load_fromFile("shaders/showNormal.vs");
    snvs->compile();
    snfs = new Shader(ShaderType_Fragment);
    snfs->load_fromFile("shaders/showNormal.fs");
    snfs->compile();
    snp = new Program();
    snp->attachShader(*snvs);
    snp->attachShader(*snfs);
    snp->link();

    rf = new RenderFrame(glm::vec2(0, 0), glm::vec2(W, H));

    //---

    //---
    Entity3D* base = Model3D::cube();
    base->setOrigin(glm::vec3(0.0, 1.0, 0.0));
    base->setSize(glm::vec3(10.0, 1.0, 10.0));
    base->setPosition(glm::vec3(5.0, 0.0, 5.0));
    scene.getEntities().insert(scene.getEntities().end(), base);

    std::vector<Model3DDefinition> dds;
    if(not IO::readOBJ("objs/Crate1.obj", dds))
    {
        std::cerr << "ERROR LOADING OBJ" << std::endl;
    }

    for(int i = 0; i < 10; i++)
    {
        for(Model3DDefinition& dd : dds)
        {
            Model3D* cube = new Model3D(dd);
            cube->setSize(glm::vec3(1, 1, 1));
            cube->setPosition(glm::vec3(0.5 + i, 0.0, 0.5));
            scene.getEntities().insert(scene.getEntities().end(), cube);
        }
    }

    scene.getCamera()->setFocus(glm::vec3(5.0, 10.0, 5.0), glm::vec3(5.0, 0.0, 5.0), glm::vec3(0.0, 0.0, -1.0));
    scene.getCamera()->setOptic_Perspective(90.f * (3.1415926535 / 180.0), 1.0, 0.1, 40.0);
    scene.getLights().insert(scene.getLights().end(), glm::vec3(5.0, 5.0, 5.0));

    Program::getDefaultDrawProgram()->use();
}

App::~App()
{
    delete rf;
    delete Program::getDefaultDrawProgram();

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
        scene.getCamera()->move(glm::vec3(0.0, 0.0, -0.1));
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        scene.getCamera()->move(glm::vec3(0.0, 0.0, 0.1));
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        scene.getCamera()->move(glm::vec3(-0.1, 0.0, 0.0));
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        scene.getCamera()->move(glm::vec3(0.1, 0.0, 0.0));
    }
}

void App::draw() const
{
    rf->clean();
    scene.draw(*rf);
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
        app->scene.getEntities().back()->translate(glm::vec3(0, 0, -1));
    }

    if(GLFW_KEY_S == key)
    {
        app->scene.getEntities().back()->translate(glm::vec3(0, 0, 1));
    }

    if(GLFW_KEY_A == key)
    {
        app->scene.getEntities().back()->translate(glm::vec3(-1, 0, 0));
    }

    if(GLFW_KEY_D == key)
    {
        app->scene.getEntities().back()->translate(glm::vec3(1, 0, 0));
    }

    if(GLFW_KEY_N == key)
    {
        app->scene.getEntities().back()->rotateY(PI/4.f);
    }

    if(GLFW_KEY_M == key)
    {
        app->scene.getEntities().back()->rotateZ(PI/4.f);
    }
}

void App::callback_cursor(GLFWwindow *window, double xpos, double ypos)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));

    double diffX = xpos - app->W/2;
    app->scene.getCamera()->rotateX_VRP(-diffX / 360.f);

    double diffY = ypos - app->H/2;
    app->scene.getCamera()->rotateY_VRP(-diffY / 360.f);

    glfwSetCursorPos(window, app->W/2, app->H/2);
}

void App::callback_resize(GLFWwindow *window, int width, int height)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
}