
#include "Scene.hpp"

#include <iostream>

Scene::Scene()
{
    cameras.push(new Camera());
}

Scene::~Scene()
{
    while(not cameras.empty())
    {
        delete cameras.top();
        cameras.pop();
    }

    for(auto it = entities.begin(); it != entities.end(); it++)
    {
        delete *it;
    }
}

void Scene::pushCamera(Camera* camera)
{
    cameras.push(camera);
}

void Scene::popCamera()
{
    delete cameras.top();
    cameras.pop();
}

Camera* Scene::getCamera()
{
    return cameras.top();
}

std::vector<glm::vec3>& Scene::getLights()
{
    return lights;
}

std::list<Entity3D*>& Scene::getEntities()
{
    return entities;
}

void Scene::draw(RenderFrame& rf, const Program* program) const
{
    program->use();
    program->setUniformValue(SUL3D_numLights, (int)lights.size());
    program->setUniformValue(SUL3D_lights, lights);
    program->setUniformValue(SUL3D_VM, cameras.top()->getVM());
    program->setUniformValue(SUL3D_PM, cameras.top()->getPM());

    for(auto it = entities.begin(); it != entities.end(); it++)
    {
        rf.draw(**it);
    }
}