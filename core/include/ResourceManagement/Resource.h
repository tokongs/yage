
#pragma once
#include <memory>
#include <iostream>

namespace yage
{

/**
     * @brief Abstract Resource class. Should be inherited by all Resources e.g. Meshes, Shaders, Textures
     * 
     */
class Resource
{

  public:
    Resource(unsigned int id, std::string name, std::string file_path);
    Resource();
    
    virtual ~Resource();

    /**
         * @brief Get the Resource Id
         * 
         * @return unsigned int 
         */
    unsigned int getResourceId();

    /**
         * @brief Get the path to where this Resource is stored
         * 
         * @return std::string 
         */
    std::string getFilePath();

    /**
         * @brief Get the name of the Resource
         * 
         * @return std::string 
         */
    std::string getName();

    void setId(int id);
    void setName(std::string name);
    void setFilePath(std::string file_path);
    
  protected:
    unsigned int m_id;
    std::string m_file_path;
    std::string m_name;
};
typedef std::shared_ptr<Resource> ResourcePtr;
} // namespace yage