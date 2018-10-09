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
     * @brief This needs to be instantiated before any other gui elements are used
     * 
     */
    class Gui{
        public:
        Gui(GLFWwindow* glfw_window_handle, unsigned int glsl_version);
        ~Gui();

        /**

        /**
         * @brief Use this at the end of the rendering loop to draw the gui elements.
         * 
         */
        void constructFrame();

        void addGuiElement(std::unique_ptr<GuiElement>);

        private:
        GLFWwindow* m_glfw_window_handle;
        std::vector<std::unique_ptr<GuiElement> > m_elements;
        unsigned int m_glsl_version;
    };
}