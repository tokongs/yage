#include "ResourceView.h"

namespace yage
{
ResourceView::ResourceView()
{
}

ResourceView::~ResourceView()
{
}

void ResourceView::setResource(ResourcePtr resource)
{
    m_resource = resource;
}

void ResourceView::constructFrame(bool independent)
{
    if(!m_resource){
        yage::YAGE_WARN("Trying to show a resource gui with no resource.");
    }
    if(independent){
        ImGui::Begin("Resource View", m_open.get());
    }
    ImGui::LabelText("Name:", m_resource->getName().c_str());
    ImGui::LabelText("File path:", m_resource->getFilePath().c_str());
    ImGui::LabelText("Resource ID:", std::to_string(m_resource->getResourceId()).c_str());


    if(independent){
        ImGui::End();
    }
    
}
} // namespace yage