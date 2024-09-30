#include "demo.h"
#include "FeatureDemo.h"
#include "ModelDemo.h"
#include "LightingDemo.h"
#include "TextureDemo.h"
#include "SpritesheetDemo.h"
#include "InterpolationDemo.h"
#include <iostream>
#include <map>
#include <memory>


/* Holds all demos */
static std::map<DemoType, std::shared_ptr<FeatureDemo>> demos;

/* Holds current demo */
static std::shared_ptr<FeatureDemo> cur_demo = nullptr;


bool demo_init(Window* win)
{
    demos[DEMO_MODEL] = std::make_shared<ModelDemo>();
    if(!demos[DEMO_MODEL]->init(win))
    {
        std::cerr << "Failed to load Model Demo" << std::endl;
        return false;
    }

    demos[DEMO_LIGHTING] = std::make_shared<LightingDemo>();
    if(!demos[DEMO_LIGHTING]->init(win))
    {
        std::cerr << "Failed to load Lighting Demo" << std::endl;
        return false;
    }

    demos[DEMO_TEXTURE] = std::make_shared<TextureDemo>();
    if(!demos[DEMO_TEXTURE]->init(win))
    {
        std::cerr << "Failed to load Texture Demo" << std::endl;
        return false;
    }

    demos[DEMO_SPRITESHEET] = std::make_shared<SpritesheetDemo>();
    if(!demos[DEMO_SPRITESHEET]->init(win))
    {
        std::cerr << "Failed to load Spritesheet Demo" << std::endl;
        return false;
    }

    demos[DEMO_INTERPOLATION] = std::make_shared<InterpolationDemo>();
    if(!demos[DEMO_INTERPOLATION]->init(win))
    {
        std::cerr << "Failed to load Interpolation Demo";
        return false;
    }


    cur_demo = demos[DEMO_MODEL];


    return true;
}

void load_demo(DemoType type)
{
    cur_demo = demos[type];
    cur_demo->on_load();
}

void demo_frame_start()
{
    cur_demo->frame_start();
}


void demo_update()
{
    cur_demo->update();
}

void demo_gui_create_frame()
{
    cur_demo->gui_create_frame();
}

void demo_draw()
{
    cur_demo->draw();
}

void demo_destroy()
{

}