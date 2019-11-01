#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GuiElement.h"

namespace yage
{
    /**
     * @brief This class is what keeps all other gui elements and renders them via ImGui.
     * The way to add elements is a little wierd so maybe it will be changed.
     * 
     */
    class Gui{
        public:
        Gui(GLFWwindow* glfwWindowHandle, unsigned int glslVersion);
        ~Gui();

        /**

        /**
         * @brief Use this at the end of the rendering loop to draw the gui elements.
         * 
         */
        void constructFrame();

        /**
         * @brief Add a gui element by handing over a unique_ptr. Either use make_unique directly as
         * a the parameter or pass a already created unique_ptr with std::move()
         * 
         */
        void addGuiElement(GuiElement *element);

        private:
        GLFWwindow* mGlfwWindowHandle;
        std::vector<GuiElement*> mElements;
        unsigned int mGlslVersion;

    };
}