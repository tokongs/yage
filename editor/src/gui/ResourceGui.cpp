#include "ResourceGui.h"

namespace yage
{
DEFINE_LOGGERS(ResourceGui);
ResourceGui::ResourceGui()
{
    INIT_LOGGERS(ResourceGui);
}

ResourceGui::~ResourceGui()
{
    FLUSH_LOGGERS(ResourceGui);
}

void ResourceGui::setResource(ResourcePtr resource)
{
    m_resource = resource;
}

void ResourceGui::constructFrame(bool independent)
{
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