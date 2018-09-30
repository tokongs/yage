#pragma once
#include <unordered_map>
#include <typeindex>
#include <stack>
#include "config.h"
#include "Util.h"
#include <string>
#include "Resource.h"
#include "ResourceLoader.h"
#include "FileReader.h"

namespace yage
{
class ResourceManager
{
public:
  ResourceManager(std::string resource_dir);
  ~ResourceManager();

  /**
   * @brief returns the resource with the correct name and type, if it has not been loaded before it will also load the resource
   * 
   * @param name of the reource
   * @param type 
   * @return ResourcePtr returns nullptr if it cannot find the resource 
   */
  template <typename T>
  int getHandle(std::string name)
  {
    auto it = m_indices.find(name);
    if (it != m_indices.end())
    {
      return it->second;
    }

    std::string file_path = m_file_paths[name];

    std::shared_ptr<ResourceLoader> loader = m_loaders[std::type_index(typeid(T))];
    ResourcePtr resource = loader->load(file_path);
    int result = -1;
    if (resource != nullptr)
    {
      

      if (m_free_ids.empty())
      {
        result = m_id;
        m_id++;
      }
      else
      {
        result = m_free_ids.top();
        m_free_ids.pop();
      }

      m_indices[name] = result;
      m_loaded_resources[result] = resource;
      resource->setId(result);
      resource->setName(name);
      resource->setFilePath(file_path);
    }

    if (result == -1)
    {
      LOG(ResourceManager, error, "Failed to load resource: " + name + " from " + m_file_paths[name]);
    }
    return result;
  }

  template <typename T>
  std::shared_ptr<T> getResource(int id)
  {
    auto it = m_loaded_resources.find(id);
    if (it != m_loaded_resources.end())
    {
      return std::dynamic_pointer_cast<T>(it->second);
    }

    LOG(ResourceManager, warn, "No resource with id: " + std::to_string(id));
    return nullptr;
  }

  /**
   * @brief Specify how the given Resource will be loaded
   * 
   * @tparam T Derived from Resource class
   * @param loader 
   */
  template <typename T>
  void registerResourceLoader(std::shared_ptr<ResourceLoader> loader)
  {
    if (!loader)
    {
      LOG(ResourceManager, error, "Trying to register nullptr as a resource loader");
      return;
    }
    m_loaders[std::type_index(typeid(T))] = loader;
  }

  /**
   * @brief Destroys the ResourcePtr of the given item
   * 
   * @param id 
   */
  void unloadResource(int id);
  ResourcePtr getResource(int id);

private:
  void buildFilePathMap(std::string resource_overview);

  std::unordered_map<int, ResourcePtr> m_loaded_resources;
  std::unordered_map<std::string, int> m_indices;
  std::unordered_map<std::type_index, std::shared_ptr<ResourceLoader>> m_loaders;
  std::unordered_map<std::string, std::string> m_file_paths;

  int m_id = 0;
  std::stack<int> m_free_ids;

  std::string m_resource_dir;

  DECLARE_LOGGERS;
};
} // namespace yage
