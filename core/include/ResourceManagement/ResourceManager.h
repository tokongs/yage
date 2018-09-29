#pragma once
#include "config.h"
#include "Util.h"
#include <unordered_map>
#include <string>
#include "Resource.h"
#include "ResourceLoader.h"
#include "FileReader.h"

namespace yage
{
class ResourceManager
{
public:
  ResourceManager(std::string resource_overview_file_path);
  ~ResourceManager();

  /**
   * @brief returns the resource with the correct name and type, if it has not been loaded before it will also load the resource
   * 
   * @param name of the reource
   * @param type 
   * @return ResourcePtr returns nullptr if it cannot find the resource 
   */
template<typename T> std::shared_ptr<T> getResource(std::string name, std::string type){
    std::shared_ptr<ResourceLoader> loader = m_loaders[type];
    ResourcePtr result = loader->load(m_file_paths[name]);
    return std::dynamic_pointer_cast<T>(result);
}

  void registerResourceLoader(std::shared_ptr<ResourceLoader> loader);

private:
  void buildFilePathMap(std::string resource_overview);

  std::unordered_map<std::string, ResourcePtr> m_loaded_resources;
  std::unordered_map<std::string, std::shared_ptr<ResourceLoader> > m_loaders;
  std::unordered_map<std::string, std::string> m_file_paths;
  std::vector<std::string> m_types;

  DECLARE_LOGGERS;
};
} // namespace yage