
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(window, app->getW()/2, app->getH()/2);

    rf = new RenderFrame(glm::ivec2(0, 0), glm::uvec2(app->getW(), app->getH()));
    shadowMap = new Texture(app->getW(), app->getH(), TextureComponent_Depth);

    Camera* cam = new Camera();
    cam->setFocus(glm::vec3(0.0, 10.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -1.0));
    cam->setOptic_Perspective(PI/2.0, 1.0, 0.1, 40.0);
    scene.pushCamera(cam);

    Camera* cam2 = new Camera();
    cam2->setFocus(glm::vec3(-10.0, 20.0, -10.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 1.0));
    cam2->setOptic_Perspective(PI/2.0, 1.0, 5.0, 40.0);
    //cam2->setOptic_Orthogonal(-20, 20, -20, 20, 5, 40);
    scene.pushCamera(cam2);

    scene.addLight(glm::vec3(-10.0, 20.0, -10.0));
    //scene.getLights().push_back(glm::vec3(-10.0, 10.0, 10.0));
    //scene.getLights().push_back(glm::vec3(10.0, 10.0, -10.0));
    //scene.getLights().push_back(glm::vec3(10.0, 10.0, 10.0));

    
    smvs = new Shader(ShaderType_Vertex);
    smvs->load_fromFile("shaders/smd.vs");
    smvs->compile();
    smfs = new Shader(ShaderType_Fragment);
    smfs->load_fromFile("shaders/smd.fs");
    smfs->compile();
    smp = new Program();
    smp->attachShader(*smvs);
    smp->attachShader(*smfs);
    smp->link();

    std::vector<Model3DDefinition> m3ds;
    IO::readOBJ("objs/terrain.obj", m3ds);

    Model3D* part = new Model3D(m3ds[0]);
    part->setPosition(glm::vec3(0.0));
    scene.addEntity(part);

    for(int i = 1; i < m3ds.size(); i++)
    {
        Model3D* part2 = new Model3D(m3ds[i]);
        part2->translate(-part->getOriginalPosition());
        scene.addEntity(part2);
    }

    up_pressed = down_pressed = left_pressed = right_pressed = false;

    //--------------- SHADOW MAP
    
    rf->clean();
    scene.draw(*rf);

    rf->sampleTexture(shadowMap);

    smp->use();
    smp->setUniformValue(3, scene.getCamera()->getVM());
    smp->setUniformValue(4, scene.getCamera()->getPM());

    scene.popCamera();
}

TestScene::~TestScene()
{
    delete rf;
    delete smp;
    delete smvs;
    delete smfs;
}

void TestScene::update()
{
    if(up_pressed) scene.getCamera()->move(glm::vec3(0.0, 0.0, -0.1));
    if(down_pressed) scene.getCamera()->move(glm::vec3(0.0, 0.0, 0.1));
    if(left_pressed) scene.getCamera()->move(glm::vec3(-0.1, 0.0, 0.0));
    if(right_pressed) scene.getCamera()->move(glm::vec3(0.1, 0.0, 0.0));

    if(l_pressed)
    {
        scene.getLights().back() += glm::vec3(5, 0, 0);
        Camera* cam2 = new Camera();
        cam2->setFocus(glm::vec3(scene.getLights().back()), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 1.0));
        cam2->setOptic_Perspective(PI/2.0, 1.0, 5.0, 40.0);
        scene.pushCamera(cam2);

        rf->clean();
        scene.draw(*rf);

        rf->sampleTexture(shadowMap);

        smp->use();
        smp->setUniformValue(3, scene.getCamera()->getVM());
        smp->setUniformValue(4, scene.getCamera()->getPM());

        scene.popCamera();

        l_pressed = false;
    }
    else if(k_pressed)
    {
        scene.getLights().back() += glm::vec3(-5, 0, 0);
        Camera* cam2 = new Camera();
        cam2->setFocus(glm::vec3(scene.getLights().back()), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 1.0));
        cam2->setOptic_Perspective(PI/2.0, 1.0, 5.0, 40.0);
        scene.pushCamera(cam2);

        rf->clean();
        scene.draw(*rf);

        rf->sampleTexture(shadowMap);

        smp->use();
        smp->setUniformValue(3, scene.getCamera()->getVM());
        smp->setUniformValue(4, scene.getCamera()->getPM());

        scene.popCamera();
        k_pressed = false;
    }
}

void TestScene::draw() const
{
    rf->clean();    
    shadowMap->bind(GL_TEXTURE1);
    scene.draw(*rf, smp);
    //scene.draw(*rf);
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
        if(key == GLFW_KEY_W) scene->up_pressed = true;
        else if(key == GLFW_KEY_S) scene->down_pressed = true; 
        else if(key == GLFW_KEY_A) scene->left_pressed = true; 
        else if(key == GLFW_KEY_D) scene->right_pressed = true;
        else if(key == GLFW_KEY_L) scene->l_pressed = true; 
        else if(key == GLFW_KEY_K) scene->k_pressed = true; 
    }

    if(action == GLFW_RELEASE)
    {
        if(key == GLFW_KEY_W) scene->up_pressed = false;
        else if(key == GLFW_KEY_S) scene->down_pressed = false; 
        else if(key == GLFW_KEY_A) scene->left_pressed = false; 
        else if(key == GLFW_KEY_D) scene->right_pressed = false; 
    }
}

void TestScene::callback_resize(GLFWwindow *window, int width, int height)
{
    TestScene* scene = static_cast<TestScene*>(glfwGetWindowUserPointer(window));
}
