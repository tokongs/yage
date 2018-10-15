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

void ResourceBrowser::constructFrame(bool independent)
{

    ResourceView rg;
    if (!*m_open)
    {
        return;
    }

    ImGui::Begin(m_title.c_str(), m_open.get());

    
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
                if (m_resource_views.find(it->second->getType()) != m_resource_views.end())
                {
                    m_resource_views[it->second->getType()]->setResource(it->second);
                    m_resource_views[it->second->getType()]->constructFrame(false);
                }
                else
                {
                    ResourceView rv;
                    rv.setResource(it->second);
                    rv.constructFrame(false);
                }
            }
        }
     

    ImGui::End();

} // namespace yage

void ResourceBrowser::addResourceView(std::string type, std::unique_ptr<ResourceView> view)
{
    m_resource_views[type] = std::move(view);
}
} // namespace yage