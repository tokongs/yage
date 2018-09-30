#include "ResourceManager.h"

namespace yage
{
DEFINE_LOGGERS(ResourceManager);
ResourceManager::ResourceManager(std::string resource_dir)
{
    INIT_LOGGERS(ResourceManager);
    FileReader reader;
    std::string resource_overview = reader.readAsString(resource_dir + "resource_overview");
    m_resource_dir = resource_dir;

    if(resource_overview.empty()){
        LOG(ResourceManager, warn, "Resource Overview File is empty");
    }

    buildFilePathMap(resource_overview);
}

ResourceManager::~ResourceManager(){
    FLUSH_LOGGERS(ResourceManager);
}

void ResourceManager::unloadResource(int id){
    for(auto it = m_indices.begin();  it != m_indices.end(); it++){
        if(it->second == id){
            m_indices.erase(it);
            break;
        }
    }
    m_loaded_resources.erase(id);
    m_free_ids.push(id);
}

void ResourceManager::buildFilePathMap(std::string resource_overview)
{
    auto it = resource_overview.find_first_of('#');
    while (it != std::string::npos)
    {   
        auto it2 = resource_overview.find_first_of('\n', it);
        std::string type = resource_overview.substr(it + 1, it2 - it - 1);
        auto it3 = resource_overview.find_first_of('\n', it2 + 1);

        while((it3 < resource_overview.find_first_of("#", it + 1) || it3 == std::string::npos) && it2 != std::string::npos){
            auto it4 = resource_overview.find_first_of(' ', it2 + 1); 

            std::string name = resource_overview.substr(it2 + 1, it4 - it2 - 1);
            std::string path;

            if(it3 != std::string::npos){
            path = resource_overview.substr(it4 + 1, it3 - it4 - 1);
            }else{
            path = resource_overview.substr(it4 + 1);
                
            }
            it2 = it3;
            it3 = resource_overview.find_first_of('\n', it2 + 1);

            m_file_paths[name] = m_resource_dir + path;
        }
    it = resource_overview.find_first_of('#', it + 1);
    }
}
} // namespace yage
