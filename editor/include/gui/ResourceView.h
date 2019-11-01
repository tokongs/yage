#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Resource.h"
#include "GuiElement.h"
#include "config.h"
#include "Logger.h"

namespace yage
{
/**
 * @brief Base class for resource detail views. Must be extended if a new type of reosurce is to be displayed
 * by the resource browser. See MeshResourceView for an example of how to do it. Basically just override the
 * constructFrame function
 * 
 */
class ResourceView : public GuiElement
{
    public:
    /**
     * @brief See GuiElement()
     * 
     * @param independent_gui 
     */
    ResourceView();
    ~ResourceView();
    
    /**
     * @brief Set the resource object to be operated on when construcing the frame
     * 
     * @param resource 
     */
    void setResource(Ref<Resource> resource);
    void constructFrame(bool independent) override;

    protected:
    Ref<Resource> mResource;
};
} // namespace yage