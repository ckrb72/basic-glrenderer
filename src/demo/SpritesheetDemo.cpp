#include "SpritesheetDemo.h"
#include <imgui.h>

bool SpritesheetDemo::init(Window* win)
{
    this->win = win;

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

}

void SpritesheetDemo::draw()
{

}

void SpritesheetDemo::on_load()
{

}

void SpritesheetDemo::gui_create_frame()
{

    static int i_scalar;
    ImGui::SeparatorText("SpriteSheet");
    ImGui::DragInt("Clip Width", &i_scalar, 1, 0, 255, "%d", ImGuiSliderFlags_None);
    ImGui::DragInt("Clip Height", &i_scalar, 1, 0, 255, "%d", ImGuiSliderFlags_None);

    ImGui::Spacing(); 

    ImGui::DragInt("Clip X", &i_scalar, 1, 0, 255, "%d", ImGuiSliderFlags_None);
    ImGui::DragInt("Clip Y", &i_scalar, 1, 0, 255, "%d", ImGuiSliderFlags_None);

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
        /* Reset values to default */
    }
}

void SpritesheetDemo::toggle_cursor()
{
    show_cursor = !show_cursor;

    /* If we want to show cursor, then we want set relative off */
    /* If we don't want to show cursor, then we want set relative on */
    win->set_cursor_relative(!show_cursor);
}