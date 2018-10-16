
#pragma once
#include <memory>
#include <iostream>

namespace yage
{

/**
     * @brief Abstract Resource class. Should be inherited by all Resources e.g. Meshes, Shaders, Textures
     * Derived classes need to override the getType function to det it to work well with the resource manager
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

    /**
     * @brief Returns a string describing the type of resource
     * 
     * @return std::string 
     */
    virtual std::string getType();
    
  protected:
    unsigned int m_id;
    std::string m_file_path;
    std::string m_name;
    std::string m_resource_type = "no_Type_Base_Resource_Class";
};
typedef std::shared_ptr<Resource> ResourcePtr;
} // namespace yage