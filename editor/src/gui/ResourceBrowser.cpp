#include "ResourceBrowser.h"

namespace yage {
    ResourceBrowser::ResourceBrowser() {
        std::unordered_map<int, Resource*> resource_map = ResourceManager::getInstance().getResourceMap();
        for (auto it = resource_map.begin(); it != resource_map.end(); it++) {
            mSelectedResource[it->second->getResourceId()] = false;
        }
    }

    ResourceBrowser::~ResourceBrowser() {
    }

    void ResourceBrowser::constructFrame(bool independent) {

        ResourceView rg;
        if (!mOpen) {
            return;
        }

        ImGui::Begin(m_title.c_str(), &mOpen);


        std::unordered_map<int, Resource*> resource_map = ResourceManager::getInstance().getResourceMap();
        if (mSelectedResource.size() < resource_map.size()) {
            mSelectedResource.clear();
            for (auto it = resource_map.begin(); it != resource_map.end(); it++) {
                if (mSelectedResource.find(it->second->getResourceId()) == mSelectedResource.end()) {
                    mSelectedResource[it->second->getResourceId()] = false;
                }
            }
        }
        for (auto it = resource_map.begin(); it != resource_map.end(); it++) {
            ImGui::Selectable(it->second->getName().c_str(), &(mSelectedResource[it->second->getResourceId()]));
            if (mSelectedResource[it->second->getResourceId()]) {
                if (mResourceViews.find(typeid(*it->second)) != mResourceViews.end()) {
                    mResourceViews[typeid(*it->second)].setResource(it->second);
                    mResourceViews[typeid(*it->second)].constructFrame(false);
                } else {
                    ResourceView rv;
                    rv.setResource(it->second);
                    rv.constructFrame(false);
                }
            }
        }


        ImGui::End();

    } // namespace yage
}