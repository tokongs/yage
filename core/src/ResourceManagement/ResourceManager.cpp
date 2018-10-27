#include "ResourceManager.h"

namespace yage
{
DEFINE_LOGGERS(ResourceManager);
ResourceManager::ResourceManager()
{
    INIT_LOGGERS(ResourceManager);
}

ResourceManager::~ResourceManager()
{
    FLUSH_LOGGERS(ResourceManager);
}

void ResourceManager::setResourceDir(std::string resource_dir)
{
    FileReader reader;
    std::string resource_overview = reader.readAsString(resource_dir + "resource_overview");
    m_resource_dir = resource_dir;

    if (resource_overview.empty())
    {
        LOG(ResourceManager, warn, "Resource Overview File is empty");
    }
    buildFilePathMap(resource_overview);
}

void ResourceManager::unloadResource(int id)
{
    for (auto it = m_indices.begin(); it != m_indices.end(); it++)
    {
        if (it->second == id)
        {
            m_indices.erase(it);
            break;
        }
    }
    m_loaded_resources.erase(id);
    m_free_ids.push(id);
}

void ResourceManager::registerPlaceholderResource(ResourcePtr resource)
{
    if (!resource)
    {
        LOG(ResourceManager, error, "Trying to load nullptr as placeholder resource");
        return;
    }
    m_placeholders[std::type_index(typeid(resource))] = resource;
}

void ResourceManager::buildFilePathMap(std::string resource_overview)
{
    auto start_of_type = resource_overview.find_first_of('#');
    while (start_of_type != std::string::npos)
    {
        auto start_of_name = resource_overview.find_first_of(' ', start_of_type + 1) + 1;
        auto start_of_path = resource_overview.find_first_of(' ', start_of_name) + 1;
        auto end_of_path = resource_overview.find_first_of('\n', start_of_path) + 1;
        if (end_of_path == std::string::npos)
        {
            end_of_path = resource_overview.size();
        }

        std::string name = resource_overview.substr(start_of_name, start_of_path - start_of_name - 1);
        std::string path = resource_overview.substr(start_of_path, end_of_path - start_of_path - 1);

        path = m_resource_dir + path;

        m_file_paths[name] = path;

        start_of_type = resource_overview.find_first_of('#', start_of_type + 1);
    }
}

std::unordered_map<int, ResourcePtr> ResourceManager::getResourceMap()
{
    return m_loaded_resources;
}
} // namespace yage
