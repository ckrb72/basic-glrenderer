#include "demo.h"
#include "FeatureDemo.h"
#include "ModelDemo.h"
#include "LightingDemo.h"
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


    cur_demo = demos[DEMO_LIGHTING];


    return true;
}

void load_demo(DemoType type)
{
    cur_demo = demos[type];
}

void demo_frame_start()
{
    cur_demo->frame_start();
}


void demo_update()
{
    cur_demo->update();
}

void demo_draw()
{
    cur_demo->draw();
}

void demo_destroy()
{

}