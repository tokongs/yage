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

            T* resource =  (T*)loader->load(file_path);
            if (resource != nullptr) {
                if(!mFreeIds.empty()){
                    mFreeIds.pop();
                }

                mIndices[name] = result;
                mLoadedResources[result] = resource;
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
        T* getResource(int id) {
            auto result = mLoadedResources.find(id);

            if (result == mLoadedResources.end())//Could not find resource, return placeholder
            {
                YAGE_WARN("Could not find resource with id: " + std::to_string(id) + ", and  type: " +
                          std::string(typeid(T).name()));
                YAGE_WARN("Returning a placeholder instead")
                auto placeholder = mPlaceholders.find(typeid(T));
                if (placeholder != mPlaceholders.end()) {
                    return (T*)(placeholder->second);
                } else {
                    YAGE_ERROR("No placeholder register for Resources of type: " + std::string(typeid(T).name()));
                    return nullptr;
                }
            }
            if (typeid(*result->second) !=
                typeid(T)) //Requested type of resource is different from what is connected to the id. Return placeholder.
            {
                YAGE_WARN("Trying to get Resource of type: " + std::string(typeid(T).name()) +
                          ". The given id returns a Resource of type: " + typeid(result->second).name());
                YAGE_WARN("Returning a placeholder instead")

                auto placeholder = mPlaceholders.find(typeid(T));
                if (placeholder != mPlaceholders.end()) {
                    return (T*)(placeholder->second);
                } else {
                    YAGE_ERROR("No placeholder registered for Resources of type: " + std::string(typeid(T).name()));
                    return nullptr;
                }
            }

            if (result != mLoadedResources.end()) //Resource found and is of right type
            {
                return (T*)(result->second);
            }
            YAGE_WARN("No resource with id: " + std::to_string(id));
            return nullptr;
        }

        /**
         * @brief Specify how the given Resource will be loaded
         *
         * @tparam T Derived from Resource class
         * @param loader
         */
        template<typename T>
        void registerResourceLoader(ResourceLoader* loader) {
            if (!loader) {
                YAGE_ERROR("Trying to register nullptr as a resource loader");
                return;
            }
            mLoaders[typeid(T)] = loader;
        }

        /**
         * @brief Register a placholder resource that will be return by getResource if the requested resource is not loaded
         *
         * @param resource
         */
        void registerPlaceholderResource(Resource* resource);

        /**
         * @brief Destroys the Resource* of the given item
         *
         * @param id
         */
        void unloadResource(int id);

        /**
         * @brief The resource dir needs to be set before using the manager
         *
         * @param res_dir
         */
        void setResourceDir(std::string res_dir);

        /**
         * @brief Returns an unordered map containing all the resources names as keys and file_paths as values
         *
         */
        std::unordered_map<int, Resource*> getResourceMap();

    private:
        void buildFilePathMap(std::string resource_overview);

        std::unordered_map<int, Resource*> mLoadedResources;
        std::unordered_map<std::type_index, Resource*> mPlaceholders;
        std::unordered_map<std::string, int> mIndices;

        std::unordered_map<std::type_index, ResourceLoader*> mLoaders;
        std::unordered_map<std::string, std::string> mFilePaths;

        int mCurrentId = 0;
        std::stack<int> mFreeIds;

        std::string mResourceDir = "";
    };
} // namespace yage
