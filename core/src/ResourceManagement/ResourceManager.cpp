#include "ResourceManager.h"

namespace yage {
    ResourceManager::ResourceManager() {
    }

    ResourceManager::~ResourceManager() {
        for (auto it : mLoadedResources) {
            if (it.second.get()) {
                delete it.second.get();
            }
        }
    }

    void ResourceManager::setResourceDir(std::string resource_dir) {
        FileReader reader;
        std::string resource_overview = reader.readAsString(resource_dir + "resource_overview");
        mResourceDir = resource_dir;

        if (resource_overview.empty()) {
            YAGE_WARN("Resource Overview File is empty");
        }
        buildFilePathMap(resource_overview);
    }

    void ResourceManager::unloadResource(int id) {
        for (auto it = mIndices.begin(); it != mIndices.end(); it++) {
            if (it->second == id) {
                mIndices.erase(it);
                break;
            }
        }
        mLoadedResources.erase(id);
        mFreeIds.push(id);
    }

/*
void ResourceManager::registerPlaceholderResource(Ref<Resource> resource)
{
    if (!resource)
    {
        YAGE_ERROR("Trying to load nullptr as placeholder resource");
        return;
    }
    mPlaceholders[typeid(*resource)] = resource;
}
*/
    void ResourceManager::buildFilePathMap(std::string resource_overview) {
        auto start_of_type = resource_overview.find_first_of('#');
        while (start_of_type != std::string::npos) {
            auto start_of_name = resource_overview.find_first_of(' ', start_of_type + 1) + 1;
            auto start_of_path = resource_overview.find_first_of(' ', start_of_name) + 1;
            auto end_of_path = resource_overview.find_first_of('\n', start_of_path) + 1;
            if (end_of_path == std::string::npos) {
                end_of_path = resource_overview.size();
            }

            std::string name = resource_overview.substr(start_of_name, start_of_path - start_of_name - 1);
            std::string path = resource_overview.substr(start_of_path, end_of_path - start_of_path - 1);

            path = mResourceDir + path;

            mFilePaths[name] = path;

            start_of_type = resource_overview.find_first_of('#', start_of_type + 1);
        }
    }

    std::unordered_map<int, Ref<Resource>> ResourceManager::getResourceMap() const {
        return mLoadedResources;
    }
} // namespace yage
