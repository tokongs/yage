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
class ResourceBrowser : public GuiElement
{
public:
  ResourceBrowser();
  ~ResourceBrowser();

  void constructFrame(bool independent) override;

  /**
     * @brief Adds a resource view for the specified resource type. If a resource has no resgistered resource view 
     * it vill display a default minimal display
     * 
     * @param resource_type Can be found in the header file of the resource
     * @param resource_view 
     */
     template<typename T>
    void addResourceView(ResourceView view)
    {
        mResourceViews[typeid(T)] = view;
    }

private:
  const std::string m_title = "Resource Browser";
  std::unordered_map<int, bool> mSelectedResource;
  std::unordered_map<std::type_index, ResourceView > mResourceViews;
};
} // namespace yage