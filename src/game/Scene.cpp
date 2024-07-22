#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{
    
}

void Scene::set_camera(Camera& camera)
{
    m_camera = &camera;

}