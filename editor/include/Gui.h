#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace yage
{
    class Gui{
        public:
        Gui(GLFWwindow* glfw_window_handle, unsigned int glsl_version);
        ~Gui();

        void startFrame();

        void render();


        private:
        GLFWwindow* m_glfw_window_handle;
        unsigned int m_glsl_version;
    };
}