
#ifndef SCENE_HPP
#define SCENE_HPP

#include "App.hpp"

class App;

class Scene
{
public:

    virtual void update() = 0;
    virtual void draw() const = 0;

    static Scene* getActiveScene();
    static void setActiveScene(Scene* scene); 

protected:

    Scene();

private:

    static Scene* activeScene;
};

#endif