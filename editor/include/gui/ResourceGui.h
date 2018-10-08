#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Resource.h"
#include "GuiElement.h"
#include "config.h"

namespace yage
{

class ResourceGui : public GuiElement
{
    public:
    /**
     * @brief See GuiElement()
     * 
     * @param independent_gui 
     */
    ResourceGui();
    ~ResourceGui();
    
    /**
     * @brief Set the resource object to be operated on when construcing the frame
     * 
     * @param resource 
     */
    void setResource(ResourcePtr resource);
    void constructFrame(bool independent) override;

    private:
    ResourcePtr m_resource;
    DECLARE_LOGGERS;
};
} // namespace yage