#include "ModelDemo.h"
#include <iostream>
#include "../core/input/input.h"
#include "../core/engine_time.h"
#include <imgui.h>
#include <graphics.h>


enum ModelType
{
    MODEL_JUPITER,
    MODEL_BACKPACK,
    MODEL_CUBE
};

enum ShaderType
{
    SHADER_NORMALS,
    SHADER_WORLD_SPACE,
    SHADER_VIEW_SPACE,
    SHADER_CLIP_SPACE
};

static int selected_model = MODEL_JUPITER;
static int selected_shader = SHADER_NORMALS;

bool ModelDemo::init(Window* win)
{
    this->win = win;


    float aspect_ratio = (float)win->get_width() / (float)win->get_height();

    cam.gen_perspective(PI / 2, (float)1920.0/ (float)1080.0, 0.1, 100.0);


    /* Load Models*/
    std::shared_ptr<Model> jupiter = std::make_shared<Model>();
    if(!jupiter->load("./assets/model/jupiter.obj"))
    {
        std::cerr << "Failed to load jupiter model" << std::endl;
        return false;
    }

    models.push_back(jupiter);

    std::shared_ptr<Model> backpack = std::make_shared<Model>();
    if(!backpack->load("./assets/model/backpack/backpack.obj"))
    {
        std::cerr << "Failed to load backpack" << std::endl;
        return false;
    }

    models.push_back(backpack);


    std::shared_ptr<Model> cube = std::make_shared<Model>();
    if(!cube->load("./assets/model/cube.fbx"))
    {
        std::cerr << "Failed to load cube" << std::endl;
        return false;
    }

    models.push_back(cube);



    /* Load shaders */
    std::shared_ptr<Shader> normals = std::make_shared<Shader>();
    if(!normals->load("./shader/normals.vert", "./shader/normals.frag"))
    {
        std::cerr << "Failed to load normals shader" << std::endl;
        return false;
    }

    shaders.push_back(normals);

    std::shared_ptr<Shader> world_space = std::make_shared<Shader>();
    if(!world_space->load("./shader/world_space.vert", "./shader/world_space.frag"))
    {
        std::cerr << "Failed to load world_space shader" << std::endl;
        return false;
    }

    shaders.push_back(world_space);

    std::shared_ptr<Shader> view_space = std::make_shared<Shader>();
    if(!view_space->load("./shader/view_space.vert", "./shader/view_space.frag"))
    {
        std::cerr << "Failed to load view_space shader" << std::endl;
        return false;
    }

    shaders.push_back(view_space);

    std::shared_ptr<Shader> clip_space = std::make_shared<Shader>();
    if(!clip_space->load("./shader/clip_space.vert", "./shader/clip_space.frag"))
    {
        std::cerr << "Failed to load clip_space shader" << std::endl;
        return false;
    }

    shaders.push_back(clip_space);


    cur_model = models[MODEL_JUPITER];
    cur_shader = shaders[SHADER_NORMALS];

    cam.position = { 0.0, 0.0, 3.0 };
    cam.forward = { 0.0, 0.0, 0.0 };
    cam.up = { 0.0, 1.0, 0.0 };

    return true;
}

void ModelDemo::draw()
{

    /* Draw currently selected model with currently selected shader */

    lnal::mat4 model(1.0);
    lnal::scale(model, model_scale);
    lnal::rotate(model, model_rotate_axis, lnal::radians(model_rotate_angle));
    lnal::translate_relative(model, model_pos);

    cur_shader->bind();
    cur_shader->set_mat4fv("model", model.data());
    cur_shader->set_mat4fv("view", cam.get_view());
    cur_shader->set_mat4fv("projection", cam.get_projection());
    cur_model->draw(*cur_shader);

}

void ModelDemo::frame_start()
{
    /* If we aren't showing the cursor, then place it in the middle of the screen */
    if(!show_cursor)
        win->set_cursor_pos(win->get_width() / 2, win->get_height() / 2);
}

void ModelDemo::update()
{
    /* Update cam position */

    if(!show_cursor)
    {
        cam.yaw += Input.Mouse.dx * cam.sensitivity;
        cam.pitch -= Input.Mouse.dy * cam.sensitivity;
        if(cam.pitch > 89.0f)
            cam.pitch = 89.0f;
        if(cam.pitch < -89.0f)
            cam.pitch = -89.0f;
    }

    if(Input.Keyboard[SDL_SCANCODE_ESCAPE] == KEY_STATE_PRESSED)
    {
        toggle_cursor();
    }

    // Camera look direction based on mouse movement
    lnal::vec3 look_dir{};
    look_dir[0] = cos(lnal::radians(cam.yaw)) * cos(lnal::radians(cam.pitch));
    look_dir[1] = sin(lnal::radians(cam.pitch));
    look_dir[2] = sin(lnal::radians(cam.yaw)) * cos(lnal::radians(cam.pitch));

    look_dir.normalize();

    // If adding a keyboard interaction here, don't forget to add the in update_keyboard_state()
    if(!show_cursor)
    {
        if(Input.Keyboard[SDL_SCANCODE_A] == KEY_STATE_HELD)
            cam.position -= Time.delta * lnal::cross(look_dir, cam.up);

        if(Input.Keyboard[SDL_SCANCODE_S] == KEY_STATE_HELD)
            cam.position -= Time.delta * look_dir;

        if(Input.Keyboard[SDL_SCANCODE_D] == KEY_STATE_HELD)
            cam.position += Time.delta * lnal::cross(look_dir, cam.up);

        if(Input.Keyboard[SDL_SCANCODE_W] == KEY_STATE_HELD)
            cam.position += Time.delta * look_dir;

        if(Input.Keyboard[SDL_SCANCODE_SPACE] == KEY_STATE_HELD)
            cam.position += Time.delta * cam.up;

        if(Input.Keyboard[SDL_SCANCODE_LSHIFT] == KEY_STATE_HELD)
            cam.position -= Time.delta * cam.up;

    }
    cam.forward = cam.position + look_dir;
    cam.lookat();
    
}



void ModelDemo::toggle_cursor()
{
    show_cursor = !show_cursor;

    /* If we want to show cursor, then we want set relative off */
    /* If we don't want to show cursor, then we want set relative on */
    win->set_cursor_relative(!show_cursor);
}

void ModelDemo::on_load()
{

}

void ModelDemo::gui_create_frame()
{
    /* Choose models here */
    /* Choose shaders too */
    /* Set scale and stuff too */

    ImGui::Spacing();

    ImGui::SeparatorText("Models");

    if(ImGui::Selectable("Jupiter", selected_model == MODEL_JUPITER) && selected_model != MODEL_JUPITER)
    {
        selected_model = MODEL_JUPITER;
        cur_model = models[selected_model];

        model_scale = 0.01;
    }

    if(ImGui::Selectable("Backpack", selected_model == MODEL_BACKPACK) && selected_model != MODEL_BACKPACK)
    {
        selected_model = MODEL_BACKPACK;
        cur_model = models[selected_model];
        model_scale = 1.0;
    }

    if(ImGui::Selectable("Cube", selected_model == MODEL_CUBE) && selected_model != MODEL_CUBE)
    {
        selected_model = MODEL_CUBE;
        cur_model = models[selected_model];
        model_scale = 1.0;
    }

    ImGui::Spacing();

    ImGui::SeparatorText("Shaders");

    if(ImGui::Selectable("Normals", selected_shader == SHADER_NORMALS) && selected_shader != SHADER_NORMALS)
    {
        selected_shader = SHADER_NORMALS;
        cur_shader = shaders[selected_shader];
    }

    if(ImGui::Selectable("World Space", selected_shader == SHADER_WORLD_SPACE) && selected_shader != SHADER_WORLD_SPACE)
    {
        selected_shader = SHADER_WORLD_SPACE;
        cur_shader = shaders[selected_shader];
    }

    if(ImGui::Selectable("View Space", selected_shader == SHADER_VIEW_SPACE) && selected_shader != SHADER_VIEW_SPACE)
    {
        selected_shader = SHADER_VIEW_SPACE;
        cur_shader = shaders[selected_shader];
    }

    if(ImGui::Selectable("Clip Space", selected_shader == SHADER_CLIP_SPACE) && selected_shader != SHADER_CLIP_SPACE)
    {
        selected_shader = SHADER_CLIP_SPACE;
        cur_shader = shaders[selected_shader];
    }

    ImGui::Spacing();

    ImGui::DragFloat3("Position", model_pos.data(), 0.05, -100.0f, 100.0f, "%.3f", ImGuiSliderFlags_None);
    ImGui::DragFloat("Scale", &model_scale, 0.001, 0.001f, 5.0f, "%.3f", ImGuiSliderFlags_None);

    ImGui::Spacing();

    ImGui::DragFloat("Rotation", &model_rotate_angle, 0.5, 0.0f, 360.0f, "%.3f", ImGuiSliderFlags_WrapAround);
    ImGui::DragFloat3("Rotation Axis", model_rotate_axis.data(), 0.05, 0.0, 10.0, "%.3f", ImGuiSliderFlags_None);

    if(ImGui::Checkbox("Wireframe", &wireframe))
    {
        toggle_wireframe();
    }
}

void ModelDemo::toggle_wireframe()
{
    if(wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}