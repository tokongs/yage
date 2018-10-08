#pragma once
#include <memory>
#include <string>
#include "imgui.h"
#include "ResourceManager.h"
#include "ResourceView.h"

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
  /**
     * @brief Adds a resource view for the specified resource type. If a resource has no resgistered resource view 
     * it vill display a default minimal display
     * 
     * @param resource_type Can be found in the header file of the resource
     * @param resource_view 
     */
  void addResourceView(std::string resource_type, std::unique_ptr<ResourceView> resource_view);

private:
  const std::string m_title = "Resource Browser";
  std::unordered_map<int, std::unique_ptr<bool>> m_selected_resource;
  std::unordered_map<std::string, std::unique_ptr<ResourceView> > m_resource_views;
  bool m_visible = true;
};
} // namespace yage