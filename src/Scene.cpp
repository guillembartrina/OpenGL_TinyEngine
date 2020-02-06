
#include "Scene.hpp"

Scene* Scene::activeScene = nullptr;

Scene::Scene() {}

Scene* Scene::getActiveScene()
{
    return activeScene;
}

void Scene::setActiveScene(Scene* scene)
{
    if(activeScene) delete activeScene;
    activeScene = scene;
} 