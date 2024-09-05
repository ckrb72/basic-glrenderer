#include "SceneManager.h"

SceneManager::SceneManager()
{}

SceneManager::~SceneManager()
{}

void SceneManager::add(const std::string& scene_name, std::shared_ptr<Scene> scene)
{
    m_scenes[scene_name] = scene;
}

void SceneManager::remove(const std::string& scene_name)
{
    m_scenes.erase(scene_name);
}

void SceneManager::change_scene(const std::string& scene_name)
{
    std::shared_ptr<Scene> new_scene = m_scenes[scene_name];

    if(new_scene != nullptr)
    {
        m_current = new_scene;
        m_current->start();
    }
}