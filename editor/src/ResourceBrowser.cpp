#include "ResourceBrowser.h"

namespace yage
{
ResourceBrowser::ResourceBrowser()
{
}

ResourceBrowser::~ResourceBrowser()
{
}

void ResourceBrowser::constructFrame()
{
    if (!m_visible)
    {
        return;
    }

    ImGui::Begin(m_title.c_str());
    std::unordered_map<std::string, std::string> resource_map = ResourceManager::getInstance().getResourceMap();
    for (auto it = resource_map.begin(); it != resource_map.end(); it++)
    {
        ImGui::Text(it->first.c_str());
    }
    ImGui::End();
}

void ResourceBrowser::setVisible(bool visible)
{
    m_visible = visible;
}
} // namespace yage