#include "gui.h"
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

static void gen_frame();


static bool light_demo = false;
static bool texture_demo = false;
static bool model_demo = false;
static bool spritesheet_demo = false;
static bool paused = false;

void gui_setup(Window& win)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(win.get_handle(), win.get_sdl_context());
    ImGui_ImplOpenGL3_Init();

}

void gui_process_event(void* event)
{
    ImGui_ImplSDL2_ProcessEvent((SDL_Event*)event);
}

void gui_create_frame()
{
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        gen_frame();
}

void gui_draw()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void gui_shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}


static void gen_frame()
{

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x, viewport->WorkPos.y), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, viewport->WorkSize.y), ImGuiCond_FirstUseEver);

    if(!ImGui::Begin("Render Library Demo", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
    {
        ImGui::End();
        return;
    }

    ImGui::SeparatorText("Press ESC to toggle mouse");

    ImGui::Spacing();

    if(ImGui::CollapsingHeader("About"))
    {
            ImGui::SeparatorText("Motivation");
            ImGui::Text("Implement a basic graphics library in c++");
            ImGui::Text("Written in standard c++20");
            ImGui::TextWrapped("Cross Platform: Works on OSX and Windows (don't notice the lack of any mention of linux)");
            ImGui::Text("OpenGL 4.1 API used for all graphics operations");

            ImGui::Spacing();

            ImGui::SeparatorText("Features");
            ImGui::BulletText("Blinn Shading");
            ImGui::BulletText("Texture Loading");
            ImGui::BulletText("Model Loading");
            ImGui::BulletText("Spritesheet Animations");
            ImGui::BulletText("Programmable Shaders");
            ImGui::BulletText("Moveable Camera");
            ImGui::BulletText("Homemade Linear Algebra Library");
            ImGui::BulletText("Basic Scene System (Not Shown in Demo)");

            ImGui::Spacing();

            ImGui::SeparatorText("Planned Features (If And When I Have Time)");
            ImGui::BulletText("Library Rewrite");
            ImGui::BulletText("Batch Rendering");
            ImGui::BulletText("Text Rendering");
            ImGui::BulletText("Multithreaded Model Loading");
            ImGui::BulletText("Shader Magic");
            ImGui::BulletText("Gizmos");
            ImGui::BulletText("File IO");
            ImGui::BulletText("3D Animations via Bones");
            ImGui::BulletText("Physics Integration");
            ImGui::BulletText("Input System");
            ImGui::BulletText("Audio System");

            ImGui::Spacing();

            ImGui::SeparatorText("External Libraries"); 
            ImGui::BulletText("Dear ImGui: GUI Display");
            ImGui::BulletText("SDL2: Windowing");
            ImGui::BulletText("GLAD: Loading OpenGL Functions (Only on Windows)");
            ImGui::BulletText("Assimp: Loading Model Files From Disk");
            ImGui::BulletText("STB Image: Loading Images Files From Disk");
    }

    if(ImGui::CollapsingHeader("Learning Resources"))
    {
        ImGui::Text("Want to Learn More?");
        ImGui::Text("Here Are Some Resources That Helped Me!");
        ImGui::Separator();

        ImGui::Text("LearnOpenGL: OpenGL Basics");
        ImGui::Text("ScratchPixel: Math Derivations and Graphics Basics");
        ImGui::Text("songho.ca: Math Derivations and Graphics Basics");
    }

    if(ImGui::CollapsingHeader("Demos"))
    {
        /* FIXME: */
        /* These should be selectables not buttons */
        ImVec2 placeholder(0.0, 0.0);
        if(ImGui::Button("Textures"))
        {
            texture_demo = !texture_demo;
            /* Send EVENT_DEMO_SWITCH to event dispatcher and then switch demo */
        }


        if(ImGui::Button("Lighting"))
        {
            light_demo = !light_demo;
        }


        if(ImGui::Button("Models"))
        {
            model_demo = !model_demo;
        }

        if(ImGui::Button("Spritesheet"))
        {
            spritesheet_demo = !spritesheet_demo;
        }
    }

    ImGui::Spacing();

    static float f_vec[3] = { 0.0f, 0.0f, 0.0f };
    static float light_color[3] = { 0.0f, 0.0f, 0.0f };
    static float f_scalar = 0.0f;
    static int i_scalar = 0;

    if(light_demo)
    {
        ImGui::SeparatorText("Model");
        ImGui::DragFloat3("Position", f_vec, 0.05, -100.0f, 100.0f, "%.3f", ImGuiSliderFlags_None);
        ImGui::DragFloat("Rotation", &f_scalar, 0.1, -360.0f, 360.0f, "%.3f", ImGuiSliderFlags_None);

        ImGui::SeparatorText("Light");
        ImGui::DragFloat("Position", &f_scalar, 0.1, -360.0f, 360.0f, "%.3f", ImGuiSliderFlags_None);
        ImGui::ColorEdit3("Color", light_color);
    }

    if(texture_demo)
    {
        ImGui::SeparatorText("Texture");
        ImGui::ColorEdit3("Color", light_color);
    }

    if(spritesheet_demo)
    {
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

    static bool wireframe = false;

    if(model_demo)
    {
        /* Choose models here */
        /* Choose shaders too */
        /* Set scale and stuff too */

        ImGui::SeparatorText("Model");

        static bool selected = true;

        if(ImGui::Selectable("Model 1", selected))
        {
            selected = !selected;
        }

        if(ImGui::DragFloat3("Position", f_vec, 0.05, -100.0f, 100.0f, "%.3f", ImGuiSliderFlags_None))
        {
            std::cout << "Position changed" << std::endl;
            /* Send EVENT_POSITION_CHANGED to event dispatcher */
        }

        ImGui::DragFloat("Scale", &f_scalar, 0.01, 0.001f, 5.0f, "%.3f", ImGuiSliderFlags_None);
        ImGui::DragFloat("Rotation", &f_scalar, 0.1, -360.0f, 360.0f, "%.3f", ImGuiSliderFlags_None);
        ImGui::Checkbox("Wireframe", &wireframe);


    }

    ImGui::End();
}