#include "SpritesheetDemo.h"
#include <imgui.h>
#include <iostream>
#include "../core/engine_time.h"

bool SpritesheetDemo::init(Window* win)
{
    this->win = win;

    cam.gen_perspective(PI / 2, ((float)win->get_width()) / ((float)win->get_height()), 0.1, 10.0);

    if(!sprite_sheet.load("./assets/img/skeleton_death.png"))
    {
        std::cerr << "Failed to load skeleton spritsheet" << std::endl;
        return false;
    }

    if(!sprite_shader.load("./shader/splash.vert", "./shader/splash.frag"))
    {
        std::cerr << "Failed to load spritesheet shader" << std::endl;
        return false;
    }

    sprite_sheet.set_clip(clip_x, clip_y);
    sprite_sheet.set_size(clip_width, clip_height);

    lnal::translate_relative(model, lnal::vec3(0.0, 0.0, -2.0));

    return true;
}

void SpritesheetDemo::frame_start()
{
    /* If we aren't showing the cursor, then place it in the middle of the screen */
    if(!show_cursor)
        win->set_cursor_pos(win->get_width() / 2, win->get_height() / 2);
}

void SpritesheetDemo::update()
{

    sprite_sheet.set_clip(clip_x, clip_y);
    sprite_sheet.set_size(clip_width, clip_height);

    if(!paused)
    {
        if(time >= (1 / (float)fps))
        {
            clip_x += clip_width;
            clip_x = clip_x % 495;
            sprite_sheet.set_clip(clip_x, 0);
            time = 0.0f;
        }

        time += Time.delta;
    }
}

void SpritesheetDemo::draw()
{
    sprite_shader.bind();

    sprite_shader.set_mat4fv("model", model.data());
    sprite_shader.set_mat4fv("view", cam.get_view());
    sprite_shader.set_mat4fv("projection", cam.get_projection());
    sprite_shader.set_int("sprite_sheet", 0);

    sprite_sheet.draw();
}

void SpritesheetDemo::on_load()
{

}

void SpritesheetDemo::gui_create_frame()
{
    ImGui::SeparatorText("SpriteSheet");
    ImGui::DragInt("Clip Width", &clip_width, 1, 0, 255, "%d", ImGuiSliderFlags_None);
    ImGui::DragInt("Clip Height", &clip_height, 1, 0, 255, "%d", ImGuiSliderFlags_None);

    ImGui::Spacing(); 

    ImGui::DragInt("Clip X", &clip_x, 1, 0, 255, "%d", ImGuiSliderFlags_None);
    ImGui::DragInt("Clip Y", &clip_y, 1, 0, 255, "%d", ImGuiSliderFlags_None);

    ImGui::Spacing();
    
    ImGui::DragInt("FPS", &fps, 1, 0, 255, "%d", ImGuiSliderFlags_None);

    std::string pause_str;
    if(paused)
        pause_str = "Play";
    else
        pause_str = "Pause";

    if(ImGui::Button(pause_str.c_str()))
    {
        paused = !paused;
    }

    ImGui::SameLine();

    if(ImGui::Button("Reset"))
    {
        clip_width = 33;
        clip_height = 32;
        clip_x = 0;
        clip_y = 0;
    }
}

void SpritesheetDemo::toggle_cursor()
{
    show_cursor = !show_cursor;

    /* If we want to show cursor, then we want set relative off */
    /* If we don't want to show cursor, then we want set relative on */
    win->set_cursor_relative(!show_cursor);
}