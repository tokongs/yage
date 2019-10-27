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
#include <rapidxml/rapidxml.hpp>
#include <filesystem>

namespace yage {

    typedef std::unordered_map<std::string, Resource*> ResourceMap;

    class ResourceManager : public Singleton<ResourceManager> {
    public:
        ResourceManager();

        ~ResourceManager();

        /**
         * @brief returns the resource with the correct name and type, if it has not been loaded before it will also load the resource
         *
         * @param name of the reource
         * @param type
         * @return Resource* returns nullptr if it cannot find the resource
         */
        template<typename T>
        int getHandle(std::string name) {
            auto it = mIndices.find(name);
            if (it != mIndices.end()) // Returns the handle if the resource is already loaded
            {
                return it->second;
            }

            std::string file_path = mFilePaths[name];

            //find the associated loader and load the resource
            ResourceLoader* loader = mLoaders[std::type_index(typeid(T))];

            int result = -1;
            if (mFreeIds.empty()) {
                result = mCurrentId;
                mCurrentId++;
            } else {
                result = mFreeIds.top();
            }

            Resource* resource =  (T*)loader->load(file_path);
            if (resource) {
                if(!mFreeIds.empty()){
                    mFreeIds.pop();
                }

                mIndices[name] = result;
                mLoadedResources[result] = Ref<Resource>(resource);
                resource->setId(result);
                resource->setName(name);
                resource->setFilePath(file_path);
            }

            if (result == -1) {
                YAGE_ERROR("Failed to load resource: " + name + " from " + mFilePaths[name]);
            }
            return result;
        }

        /**
       * @brief Get a pointer to a resource with id. Return a placholder resource if the type requested is different
       * from what is loaded and connected to the id. Also returns a placholder if the id is not found. If no placeholder is registered it will
       * return a nullptr as a last resort.
       *
       * @tparam T
       * @param id
       * @return std::shared_ptr<T>
       */
        template<typename T>
        Ref<T> getResource(int id) {
            auto result = mLoadedResources.find(id);

            if (result != mLoadedResources.end())
            {
                return result->second;
            }
            YAGE_WARN("No resource with id: " + std::to_string(id));
            return nullptr;
        }

        /**
         * @brief Specify how the given Resource will be loaded
         *
         * @tparam T Derived from Resource class
         * @param resourceTypeName type the xml file
         * @param loader
         */
        template<typename T>
        void registerResourceLoader(std::string resourceTypeName, ResourceLoader* loader) {
            if (!loader) {
                YAGE_ERROR("Trying to register nullptr as a resource loader");
                return;
            }
            mLoaders[typeid(T)] = loader;
        }

        void loadAllResources();
        std::vector<std::string> traverseDirectories(std::string baseDir);

        /**
         * @brief The resource dir needs to be set before using the manager
         *
         * @param res_dir
         */
        void setResourceDir(std::string res_dir);
        std::unordered_map<int, Ref<Resource>> getResourceMap() const;

    private:
        void buildFilePathMap(std::string resource_overview);

        std::unordered_map<int, Ref<Resource>> mLoadedResources;
        std::unordered_map<std::type_index, Ref<Resource>> mPlaceholders;
        std::unordered_map<std::string, int> mIndices;

        std::unordered_map<std::type_index, ResourceLoader*> mLoaders;
        std::unordered_map<std::string, std::type_index> xmlTypeToTypeIndex;
        std::unordered_map<std::string, std::string> mFilePaths;

        int mCurrentId = 0;
        std::stack<int> mFreeIds;

        std::string mResourceDir = "";
    };
} // namespace yage
