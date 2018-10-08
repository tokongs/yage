#include "Gui.h"

namespace yage
{
Gui::Gui(GLFWwindow *glfw_window_handle, unsigned int glsl_version)
    : m_glfw_window_handle(glfw_window_handle),
      m_glsl_version(glsl_version)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;

    ImGui_ImplGlfw_InitForOpenGL(m_glfw_window_handle, true);
    std::string verison_string = "#version " + std::to_string(m_glsl_version);
    ImGui_ImplOpenGL3_Init(verison_string.c_str());

    // Setup style
    ImGui::StyleColorsDark();
}

Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Gui::startFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
} // namespace yage