
#ifndef SCENE_HPP
#define SCENE_HPP

#include <stack>
#include <list>

#include "Camera.hpp"
#include "Enums.hpp"
#include "Entity3D.hpp"
#include "RenderFrame.hpp"

class Scene
{
public:

    Scene();
    ~Scene();

    void pushCamera(Camera* camera);
    void popCamera();

    Camera* getCamera();
    std::vector<glm::vec3>& getLights();
    std::list<Entity3D*>& getEntities();

    void draw(RenderFrame& rf, const Program* program = Program::getDefaultDrawProgram()) const;

private:

    std::stack<Camera*> cameras;
    std::vector<glm::vec3> lights;
    std::list<Entity3D*> entities;
};

#endif