#include "gui.h"
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

static void gen_frame();

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
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

    if(!ImGui::Begin("Render Library Demo", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
    {
        ImGui::End();
        return;
    }

    if(ImGui::BeginMenuBar())
    {
        ImGui::Text("Render Library Demo");

        ImGui::EndMenuBar();
    }

    ImGui::BeginChild("About");

    if(ImGui::CollapsingHeader("About"))
    {
            ImGui::SeparatorText("Motivation");
            ImGui::Text("Implement a basic graphics library in c++");
            ImGui::Text("Written in standard c++20");
            ImGui::Text("Cross Platform: Works on OSX and Windows");
            ImGui::Text("(not tested on Linux systems but probably works");
            ImGui::Text("[massive coping] )");
            ImGui::Text("OpenGL 4.1 API used for all graphics operations");

            ImGui::Spacing();

            ImGui::SeparatorText("Features");
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
        ImVec2 placeholder(0.0, 0.0);
        ImGui::Button("Lighting", placeholder);
        ImGui::Button("Models");
        ImGui::Button("Spritesheet");
        ImGui::Button("Shaders");
    }


    ImGui::EndChild();



    ImGui::End();
}