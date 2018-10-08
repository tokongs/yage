#include "ResourceBrowser.h"

namespace yage
{
ResourceBrowser::ResourceBrowser()
{
    std::unordered_map<int, ResourcePtr> resource_map = ResourceManager::getInstance().getResourceMap();
    for (auto it = resource_map.begin(); it != resource_map.end(); it++)
    {
        m_selected_resource[it->second->getResourceId()] = std::make_unique<bool>(false);
    }
}

ResourceBrowser::~ResourceBrowser()
{
}

void ResourceBrowser::constructFrame()
{

    ResourceGui rg;
    if (!m_visible)
    {
        return;
    }

    ImGui::Begin(m_title.c_str());
    std::unordered_map<int, ResourcePtr> resource_map = ResourceManager::getInstance().getResourceMap();
    if (m_selected_resource.size() < resource_map.size())
    {
        m_selected_resource.clear();
        for (auto it = resource_map.begin(); it != resource_map.end(); it++)
        {
            if (m_selected_resource.find(it->second->getResourceId()) == m_selected_resource.end())
            {
                m_selected_resource[it->second->getResourceId()] = std::make_unique<bool>(false);
            }
        }
    }
    for (auto it = resource_map.begin(); it != resource_map.end(); it++)
    {
        ImGui::Selectable(it->second->getName().c_str(), m_selected_resource[it->second->getResourceId()].get());
        if (*m_selected_resource[it->second->getResourceId()].get())
        {
            rg.setResource(it->second);
            rg.constructFrame(false);
        }
    }
    ImGui::End();
}

void ResourceBrowser::setVisible(bool visible)
{
    m_visible = visible;
}
} // namespace yage