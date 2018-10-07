#include "ResourceBrowser.h"

namespace yage
{
ResourceBrowser::ResourceBrowser()
{
    for (int i = 0; i < ResourceManager::getInstance().getResourceMap().size(); i++)
    {
        m_selected_resource.push_back(std::make_unique<bool>(false));
    }
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
    if (m_selected_resource.size() < resource_map.size())
    {
        m_selected_resource.clear();
        for (int i = 0; i < ResourceManager::getInstance().getResourceMap().size(); i++)
        {
            m_selected_resource.push_back(std::make_unique<bool>(false));
        }
    }
    ImGui::BeginCombo("scrolling", "test");
    int i = 0;
    for (auto it = resource_map.begin(); it != resource_map.end(); it++)
    {
        ImGui::Selectable(it->first.c_str(), m_selected_resource[i].get());
        if(*m_selected_resource[i].get()){
        }
        i++;
    }
    ImGui::EndChild();

    ImGui::End();
}

void ResourceBrowser::setVisible(bool visible)
{
    m_visible = visible;
}
} // namespace yage