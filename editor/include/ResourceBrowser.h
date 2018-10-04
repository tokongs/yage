#pragma once
#include <memory>
#include <string>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ResourceManager.h"

namespace yage
{
/**
 * @brief An imgui window for browsing resources
 * 
 */
class ResourceBrowser
{
  public:
    ResourceBrowser();
    ~ResourceBrowser();

    void constructFrame();
    
    void setVisible(bool visible);
  private:
    const std::string m_title = "Resource Browser";
    bool m_visible = true;
};
} // namespace yage