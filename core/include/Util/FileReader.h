#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <Util.h>
#include <memory>
#include <config.h>
#include "Logger.h"

namespace yage
{
class FileReader
{
  public:
  /**
   * @brief Construct a new File Reader object
   * 
   * @param root_dir Optional arugment to set another root directory
   */
    FileReader(std::string root_dir = "");
    ~FileReader();

    /**
         * @brief Opens up a file and returns it's conent as a string. 
         * 
         * @param file_name 
         * @return std::string 
         */
    std::string readAsString(std::string filePath);

    /**
     * @brief Changes the root directory
     * 
     * @param dir 
     */
    void changeRootDir(std::string dir);
    
    /**
     * @brief Checks if file exists
     * 
     * @param file 
     * @return true 
     * @return false 
     */
    bool fileExists(std::string file);

    /**
     * @brief Returns the root directory as a string
     * 
     * @return std::string 
     */
    std::string getRootDir();

  private:
    std::string mRootDir;

};
} // namespace yage