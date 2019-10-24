#pragma once
#include "Resource.h"
#include <string>

namespace yage
{
    /**
     * @brief Base class for a resource loader. To load new resources create a child of this class and resgister it in the resource manager
     * 
     * 
     */
class ResourceLoader
{
  public:
  /**
   * @brief Construct a new Resource Loader object and specify the type of resource it loads
   * 
   * @param type 
   */
    ResourceLoader();
    ~ResourceLoader();

    /**
     * @brief This class needs to be overridden to load the specified resource
     * 
     * @return ResourcePtr 
     */
    virtual ResourcePtr load(int id, std::string name, std::string filepath) = 0;
};
} // namespace yage