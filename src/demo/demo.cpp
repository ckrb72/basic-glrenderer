#include "demo.h"
#include "FeatureDemo.h"
#include "ModelDemo.h"
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
    if(!demos[DEMO_MODEL]->init_demo(win))
    {
        std::cerr << "Failed to load Model Demo" << std::endl;
        return false;
    }


    cur_demo = demos[DEMO_MODEL];


    return true;
}

void load_demo(DemoType type)
{
    cur_demo = demos[type];
}


void demo_update()
{
    cur_demo->update_demo();
}

void demo_draw()
{
    cur_demo->draw_demo();
}

void demo_destroy()
{

}