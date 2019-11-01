
#pragma once
#include <memory>
#include <iostream>
#include "Reference.h"

namespace yage
{

/**
     * @brief Abstract Resource class. Should be inherited by all Resources e.g. Meshes, Shaders, Textures
     * 
     */
class Resource : public Reference
{

  public:
    Resource(unsigned int id, std::string name, std::string filePath);
    Resource();
    
    virtual ~Resource() = default;

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
    void setFilePath(std::string filePath);
    
  protected:
    unsigned int mID;
    std::string mFilePath;
    std::string mName;
};
} // namespace yage