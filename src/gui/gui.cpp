#include "gui.h"
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include "../demo/demo.h"
#include <iostream>

static void gen_frame();

static int selected_demo = 0;
static bool paused = false;

enum SELECTED_DEMO
{
    MODEL,
    LIGHTING,
    TEXTURE,
    SPRITESHEET
};


static bool booleans[5] = {0};

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
            ImGui::BulletText("Phong Shading");
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

        if(ImGui::Selectable("Model", selected_demo == MODEL) && selected_demo != MODEL)
        {
            selected_demo = 0;
            load_demo(DEMO_MODEL);
        }

        if(ImGui::Selectable("Lighting", selected_demo == LIGHTING) && selected_demo != LIGHTING)
        {
            selected_demo = 1;
            load_demo(DEMO_LIGHTING);
        }

        if(ImGui::Selectable("Textures", selected_demo == TEXTURE) && selected_demo != TEXTURE)
        {
            selected_demo = 2;
            load_demo(DEMO_TEXTURE);
        }

        if(ImGui::Selectable("Spritesheet", selected_demo == SPRITESHEET) && selected_demo != SPRITESHEET)
        {
            selected_demo = 3;
            load_demo(DEMO_SPRITESHEET);
        }
    }

    static float f_vec[3];
    static float light_color[3];
    static float f_scalar;
    static int i_scalar;


    if(selected_demo == SPRITESHEET)
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

    demo_gui_create_frame();

    ImGui::End();
}