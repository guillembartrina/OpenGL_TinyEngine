
#include "App.hpp"

#include <iostream>

#include "IO.hpp"
#include "Model3D.hpp"

#define printWarning(x) (std::cout<<"> Warning: "<<x<<std::endl)

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

    rf = new RenderFrame(glm::vec2(0, 0), glm::vec2(W, H));

    //---

    vs = new Shader(ShaderType::Vertex);
    vs->load_fromFile("shaders/draw.vs");
    //vs->load_default();
    if(!vs->compile()) std::cout << "ERROR1!" << std::endl;

    fs = new Shader(ShaderType::Fragment);
    fs->load_fromFile("shaders/draw.fs");
    //fs->load_default();
    if(!fs->compile()) std::cout << "ERROR2!" << std::endl;

    program = new Program();
    program->attachShader(*vs);
    program->attachShader(*fs);
    program->link();
    
    //---

    rf->getCamera()->setFocus(glm::vec3(1609, 12, -95), glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0));
    //rf->getCamera()->setOptic_Orthogonal(-5, 5, -5, 5, 0.1, 40.0);
    rf->getCamera()->setOptic_Perspective(90.f * (3.1415926535 / 180.0), 1.0, 0.1, 40.0);

    rf->getLights().push_back(glm::vec3(1609, 40, -95));

    //rf->camera.applyResize(W, H);

    //---

    txt = new Texture("textures/cat.jpg");
    rect = new Rectangle(glm::vec2(500, 500), glm::vec2(800, 800), txt);

    std::vector<DrawableDefinition> dd;
    if(not IO::readOBJ("objs/Test.obj", dd))
    {
        std::cerr << "ERROR LOADING OBJ" << std::endl;
    }

    for(DrawableDefinition& d : dd)
    {
        drawables.push_back(new Model3D(d));
    }

    //trp = new TestRP();

    glDisable(GL_CULL_FACE);
}

App::~App()
{
    for(unsigned int i = 0; i < drawables.size(); i++)
    {
        delete drawables[i];
    }

    delete program;
    delete rf;
    //delete trp;
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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        rf->getCamera()->move(glm::vec3(0.0, 0.0, -0.1));
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        rf->getCamera()->move(glm::vec3(0.0, 0.0, 0.1));
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        rf->getCamera()->move(glm::vec3(-0.1, 0.0, 0.0));
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        rf->getCamera()->move(glm::vec3(0.1, 0.0, 0.0));
    }
}

void App::draw() const
{   
    //program->use();
    rf->startDrawing();
    for(int i = 0; i < drawables.size(); i++)
    {
        rf->draw(*drawables[i]);
    }
    //rf->render(*trp);
    //rf->drawOnSurface(*rect);
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