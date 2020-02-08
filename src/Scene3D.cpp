
#include "Scene3D.hpp"

#include <iostream>

Scene3D::Scene3D() {}

Scene3D::~Scene3D()
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

void Scene3D::pushCamera(Camera* camera)
{
    cameras.push(camera);
}

void Scene3D::popCamera()
{
    delete cameras.top();
    cameras.pop();
}

Camera* Scene3D::getCamera()
{
    return cameras.top();
}

void Scene3D::addLight(const glm::vec3& light)
{
    lights.push_back(light);
}

std::vector<glm::vec3>& Scene3D::getLights()
{
    return lights;
}

void Scene3D::addEntity(Entity3D* entity)
{
    entities.insert(entities.end(), entity);
}

std::list<Entity3D*>& Scene3D::getEntities()
{
    return entities;
}

void Scene3D::draw(RenderFrame& rf, const Program* program) const
{
    if(not cameras.empty())
    {
        if(program != nullptr) program->use();
        Program::getActiveProgram()->setUniformValue(SUL3D_numLights, (int)lights.size());
        Program::getActiveProgram()->setUniformValue(SUL3D_lights, lights);
        Program::getActiveProgram()->setUniformValue(SUL3D_VM, cameras.top()->getVM());
        Program::getActiveProgram()->setUniformValue(SUL3D_PM, cameras.top()->getPM());

        for(auto it = entities.begin(); it != entities.end(); it++)
        {
            rf.draw(**it);
        }
    }
    else
    {
        std::cerr << "Scene3D: error drawing, not camera defined" << std::endl;
    }
}