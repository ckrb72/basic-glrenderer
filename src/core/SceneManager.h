#pragma once
#include "Scene.h"
#include <memory>
#include <string>
#include <map>

class SceneManager
{
private:

    std::map<std::string, std::shared_ptr<Scene>> m_scenes;

    std::shared_ptr<Scene> m_current = nullptr;

public:

    SceneManager();
    ~SceneManager();

    void add(const std::string& scene_name, std::shared_ptr<Scene> scene);
    void remove(const std::string& scene_name);
    void change_scene(const std::string& scene_name);

};