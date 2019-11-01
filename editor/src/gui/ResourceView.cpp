#include "ResourceView.h"

namespace yage
{
ResourceView::ResourceView()
{
}

ResourceView::~ResourceView()
{
}

void ResourceView::setResource(Ref<Resource> resource)
{
    mResource = resource;
}

void ResourceView::constructFrame(bool independent)
{
    if(!mResource){
        yage::YAGE_WARN("Trying to show a resource gui with no resource.");
    }
    if(independent){
        ImGui::Begin("Resource View", &mOpen);
    }
    ImGui::LabelText("Name:", mResource->getName().c_str());
    ImGui::LabelText("File path:", mResource->getFilePath().c_str());
    ImGui::LabelText("Resource ID:", std::to_string(mResource->getResourceId()).c_str());
    ImGui::LabelText("Reference count", std::to_string(mResource->getRefCount()).c_str());


    if(independent){
        ImGui::End();
    }
    
}
} // namespace yage