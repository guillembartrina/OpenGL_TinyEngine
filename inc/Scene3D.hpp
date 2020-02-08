
#ifndef SCENE3D_HPP
#define SCENE3D_HPP

#include <vector>
#include <stack>
#include <list>

#include "Enums.hpp"
#include "Camera.hpp"
#include "Entity3D.hpp"
#include "RenderFrame.hpp"
#include "Program.hpp"

class Scene3D
{
public:

    Scene3D();
    ~Scene3D();

    void pushCamera(Camera* camera);
    void popCamera();
    Camera* getCamera();

    void addLight(const glm::vec3& light);
    std::vector<glm::vec3>& getLights();

    void addEntity(Entity3D* entity);
    std::list<Entity3D*>& getEntities();

    void draw(RenderFrame& rf, const Program* program = Program::getDefaultDrawProgram()) const;

private:

    std::stack<Camera*> cameras;
    std::vector<glm::vec3> lights;
    std::list<Entity3D*> entities;
};

#endif