#include "Gui.h"

namespace yage
{
Gui::Gui(GLFWwindow *glfwWindowHandle, unsigned int glslVersion)
    : mGlfwWindowHandle(glfwWindowHandle),
      mGlslVersion(glslVersion)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui_ImplGlfw_InitForOpenGL(mGlfwWindowHandle, false);
    std::string verisonString = "#version " + std::to_string(mGlslVersion);
    ImGui_ImplOpenGL3_Init(verisonString.c_str());

    // Setup style
    ImGui::StyleColorsDark();
}

Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Gui::constructFrame()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (auto it : mElements)
    {
        it->constructFrame(true);
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::addGuiElement(GuiElement* element)
{
    mElements.push_back(element);
}
} // namespace yage