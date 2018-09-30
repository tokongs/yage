#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Window.h"
#include "GLDevice.h"
#include <glm/vec4.hpp>
#include <memory>
#include "VertexBuffer.h"
#include "Shader.h"
#include "Window.h"
#include <iostream>
#include "Util.h"
#include "FileReader.h"
#include "ResourceManager.h" 
#include "MeshLoader.h"
#include "ShaderLoader.h"
#include "Program.h"
int main(int argc, char** argv){

   

  const char* glsl_version = "#version 460";
    std::cout << getCurrentWorkingDir() << std::endl;
    yage::WindowDesc desc;
    desc.floating = true;
    desc.decorated = true;
    desc.height = 768;
    desc.width = 1024;
    desc.resizable = true;
    desc.title = "Test";
    std::shared_ptr<yage::Window> window = std::make_shared<yage::Window>(desc);

    std::shared_ptr<yage::GLDevice> device = window->getGraphicsDevice();

    yage::ResourceManager manager("/home/tokongs/projects/personal/yage/assets/");
    std::shared_ptr<yage::MeshLoader> mesh_loader = std::make_shared<yage::MeshLoader>();
    std::shared_ptr<yage::ShaderLoader> shader_loader = std::make_shared<yage::ShaderLoader>();

    manager.registerResourceLoader<yage::Mesh>(mesh_loader);
    manager.registerResourceLoader<yage::Shader>(shader_loader);


    int mesh = manager.getHandle<yage::Mesh>("box");
    int vertex = manager.getHandle<yage::Shader>("basic_vertex_shader");
    yage::Program program;
    program.attachShader(manager.getResource<yage::Shader>(vertex));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window->getWindowHandle(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    ImGui::StyleColorsDark();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    while(!window->shouldClose()){
        device->clearBuffers();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window->update();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
