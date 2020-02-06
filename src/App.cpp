
#include "App.hpp"

#include <stdexcept>

#include "TestScene.hpp"

#define printWarning(x) (std::cout<<"> Warning: "<<x<<std::endl)

App::App(const char* name, unsigned int W, unsigned int H)
{
    if(not glfwInit()) throw std::runtime_error("Failed to init GLFW");

    this->W = W;
    this->H = H;

    window = glfwCreateWindow(W, H, name, NULL, NULL);
    if(not window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create window");
	}

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    //glfwSetCursorPos(window, W/2, H/2);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);

    glewInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    Scene::setActiveScene(new TestScene(this));
}

App::~App()
{
    delete Scene::getActiveScene();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void App::run()
{
    timecount = glfwGetTime();

    while(not glfwWindowShouldClose(window))
    {
        Scene::getActiveScene()->update();
        Scene::getActiveScene()->draw();
        glfwSwapBuffers(window);
        glfwPollEvents();

        while (glfwGetTime() < (timecount + 1.0/60.0));
		timecount += 1.0/60.0;
    }
}

unsigned int App::getW() const
{
    return W;
}

unsigned int App::getH() const
{
    return H;
}


GLFWwindow* App::getWindow()
{
    return window;
}