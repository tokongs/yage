#include "ResourceView.h"

namespace yage
{
DEFINE_LOGGERS(ResourceView);
ResourceView::ResourceView()
{
    INIT_LOGGERS(ResourceView);
}

ResourceView::~ResourceView()
{
    FLUSH_LOGGERS(ResourceView);
}

void ResourceView::setResource(ResourcePtr resource)
{
    m_resource = resource;
}

void ResourceView::constructFrame(bool independent)
{
    if(!m_resource){
        LOG(ResourceView, warn, "Trying to show a resource gui with no resource.");
    }
    if(independent){
        ImGui::Begin("Resource View");
    }
    ImGui::LabelText("Name:", m_resource->getName().c_str());
    ImGui::LabelText("File path:", m_resource->getFilePath().c_str());
    ImGui::LabelText("Resource ID:", std::to_string(m_resource->getResourceId()).c_str());


    if(independent){
        ImGui::End();
    }
    
}
} // namespace yage