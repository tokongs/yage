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

    typedef std::unordered_map<std::string, ResourcePtr> ResourceMap;

    class ResourceManager : public Singleton<ResourceManager> {
    public:
        ResourceManager();

        ~ResourceManager();

        /**
         * @brief returns the resource with the correct name and type, if it has not been loaded before it will also load the resource
         *
         * @param name of the reource
         * @param type
         * @return ResourcePtr returns nullptr if it cannot find the resource
         */
        template<typename T>
        int getHandle(std::string name) {
            auto it = m_indices.find(name);
            if (it != m_indices.end()) // Returns the handle if the resource is already loaded
            {
                return it->second;
            }

            std::string file_path = m_file_paths[name];

            //find the associated loader and load the resource
            std::shared_ptr<ResourceLoader> loader = m_loaders[std::type_index(typeid(T))];

            int result = -1;
            if (m_free_ids.empty()) {
                result = m_current_id;
                m_current_id++;
            } else {
                result = m_free_ids.top();
            }

            ResourcePtr resource = loader->load(result, name, file_path);
            if (resource != nullptr) {
                if(!m_free_ids.empty()){
                    m_free_ids.pop();
                }

                m_indices[name] = result;
                m_loaded_resources[result] = resource;
                resource->setId(result);
                resource->setName(name);
                resource->setFilePath(file_path);
            }

            if (result == -1) {
                YAGE_ERROR("Failed to load resource: " + name + " from " + m_file_paths[name]);
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
        std::shared_ptr<T> getResource(int id) {
            auto result = m_loaded_resources.find(id);

            if (result == m_loaded_resources.end())//Could not find resource, return placeholder
            {
                YAGE_WARN("Could not find resource with id: " + std::to_string(id) + ", and  type: " +
                          std::string(typeid(T).name()));
                YAGE_WARN("Returning a placeholder instead")
                auto placeholder = m_placeholders.find(typeid(T));
                if (placeholder != m_placeholders.end()) {
                    return std::dynamic_pointer_cast<T>(placeholder->second);
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

                auto placeholder = m_placeholders.find(typeid(T));
                if (placeholder != m_placeholders.end()) {
                    return std::dynamic_pointer_cast<T>(placeholder->second);
                } else {
                    YAGE_ERROR("No placeholder registered for Resources of type: " + std::string(typeid(T).name()));
                    return nullptr;
                }
            }

            if (result != m_loaded_resources.end()) //Resource found and is of right type
            {
                return std::dynamic_pointer_cast<T>(result->second);
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
        void registerResourceLoader(std::shared_ptr<ResourceLoader> loader) {
            if (!loader) {
                YAGE_ERROR("Trying to register nullptr as a resource loader");
                return;
            }
            m_loaders[typeid(T)] = loader;
        }

        /**
         * @brief Register a placholder resource that will be return by getResource if the requested resource is not loaded
         *
         * @param resource
         */
        void registerPlaceholderResource(ResourcePtr resource);

        /**
         * @brief Destroys the ResourcePtr of the given item
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
        std::unordered_map<int, ResourcePtr> getResourceMap();

    private:
        void buildFilePathMap(std::string resource_overview);

        std::unordered_map<int, ResourcePtr> m_loaded_resources;
        std::unordered_map<std::type_index, ResourcePtr> m_placeholders;
        std::unordered_map<std::string, int> m_indices;

        std::unordered_map<std::type_index, std::shared_ptr<ResourceLoader>> m_loaders;
        std::unordered_map<std::string, std::string> m_file_paths;

        int m_current_id = 0;
        std::stack<int> m_free_ids;

        std::string m_resource_dir;
    };
} // namespace yage
