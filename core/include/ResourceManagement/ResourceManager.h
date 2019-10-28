#pragma once

#include <unordered_map>
#include <memory>
#include <typeindex>
#include <stack>
#include "config.h"
#include "Util.h"
#include <string>
#include "Resource.h"
#include "ResourceLoader.h"
#include "FileReader.h"
#include "Singleton.h"
#include "Logger.h"
#include "Reference.h"
#include <pugixml/pugixml.hpp>
#include <filesystem>

namespace yage {

    typedef std::unordered_map<std::string, Resource *> ResourceMap;

    class ResourceManager : public Singleton<ResourceManager> {
    public:
        ResourceManager();

        ~ResourceManager();

        template<typename T>
        Ref<T> getResource(std::string name) {
            auto result = mLoadedResources.find(name);

            if (result != mLoadedResources.end()) {
                return result->second;
            }
            YAGE_WARN("Could not find resource: {}", name);
            return nullptr;
        }

        void registerResourceLoader(std::string resourceTypeName, ResourceLoader *loader);

        void loadAllResources();

        void setResourceDir(std::string res_dir);

        std::unordered_map<std::string, Ref<Resource>> getResourceMap() const;

    private:

        void loadResource(pugi::xml_node root);

        std::vector<std::string> traverseDirectories(std::string baseDir);


        std::unordered_map<std::string, Ref<Resource>> mLoadedResources;
        std::unordered_map<std::string, ResourceLoader *> mLoaders;
        std::unordered_map<std::string, std::string> mFilePaths;

        int mCurrentId = 0;
        std::stack<int> mFreeIds;

        std::string mResourceDir = "";
    };
} // namespace yage
